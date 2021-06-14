#include "MatchDirector.h"
#include "math.h"
#include "ActionsList.h"
#include "../params.h"
#include "../navigator.h" 
#include "../odometry.h"
#include "../FsmSupervisor.h" 
#include "../actuatorSupervisor.h"
#include "Arduino.h" //NULL definition
#include "utils.h"

/**
 * @brief 
 * @file MatchDirector.cpp
 * @ingroup namespace

 */
namespace MatchDirector
{
    enum class ActionOrder {
        RecupEcueilNord,
        Phare,
        DeposeEcueilNord,
        MancheAir,
        RecupEcueilSud,
        DeposeEcueil,
    };
/*Control navigator (which is the high level interface to move the robot/give it a certain orientation) 
and FSM (which controls various actuators & execute codes depending on various states) 
depending on the time left & an order of action. 
Manage the score total, the score of an action is stored in Action. 
Can be modified by states if needed (for example, if an action is interacting with a variable amount of object & the score depend on this amount).
*/

    bool isStartingLeft = true;
    bool isDrivingBackward = false; //if move with navigator with positive number, robot goes backward

    Action *curSection = NULL; // undefined size of array
    //Section = multiple actions that usually lead to points at the end
    int curActIndex = 0;
    ActionState actionState = BEGIN;
    /**
     * @brief When there is a huge discrepancy between targeted position & position reached, this get reincremented and the same command is sent again
     *  @ingroup namespace
     */
    int nbReadjust = 0; //

    float timer = 10; // en s, durée du match
    int score = 0;
    float offsetX = 0; //offsets au début du terrain par rapport à l'abs
    float offsetY = 0;
    uint32_t start_millis;
    bool moveBackToBase;


void init()
{
    start_millis = millis();
    moveBackToBase = false;
    //TODO : call only when match has started;
    //TODO : implement timer count;

    //en fonction de la taille du terrain 

    offsetY = 1000.0f; //largeur terrain/2
    offsetX = (isStartingLeft) ? robot_center_x : (3000.0f - robot_center_x); //3000-> longueur terrain
    //DEBUG : 
    //curSection = EcocupsTopLeft;
}

float distance_squared (float xA, float yA, float xB, float yB)
{
    return (xA-xB)*(xA-xB)+(yA-yB)*(yA-yB);
}

void abs_coords_to(float x, float y)
{  
    //SerialCtrl.print("commande envoyé : move_to local : ");
    navigator.move_to(abs_x_to_local(x), abs_x_to_local(y));
    
}

float abs_x_to_local(float x)
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -x + offsetX;
    }
    else
    {
        return x - offsetX;
    }
}

float abs_y_to_local(float y)
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -y + offsetY;
    }
    else
    {
        return y - offsetY;
    }
}

float get_abs_x()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -odometry_motor.get_pos_x() + offsetX;
    }
    else 
    {
        return odometry_motor.get_pos_x() + offsetX;
    }
}

float get_abs_y()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -odometry_motor.get_pos_y() + offsetY;
    }
    else 
    {
        return odometry_motor.get_pos_y() + offsetY;
    }
}
float timeToReachCoords(float begX, float begY, float targetX, float targetY)
/* rough estimate using ACCEL MAX, doesn't take into account time to turn to a certain angle*/
{
    float time = 0;
    float distance = sqrt((targetX-begX)*(targetX-begX)+(begY-targetY)*(begY-targetY));
    
    if(distance >= ACCEL_MAX)
    {
         time = distance/(ACCEL_MAX) + 2; //trapèze de vitesse majorée
    }
    else
    {
        float speed = ACCEL_MAX / 2;
        time = distance/speed + 1;
    }
    return time;

}

//Handle the logic/state of an action : should it move, should it execute the next state,...
void action_dispatcher(Action action)
{
    if(actionState == BEGIN)
    {
        SerialCtrl.print("new action :");
        SerialCtrl.print("\t");
        SerialCtrl.print(action.x);
        SerialCtrl.print("\t");
        SerialCtrl.print(action.y);
        SerialCtrl.print("\t");
        SerialCtrl.println(action.angle);
        //SerialCtrl.println("actionState == begin");
        abs_coords_to(action.x,action.y);
        actionState = MOVING;
    }

    else if(actionState == MOVING)
    {
        if (navigator.isTrajectoryFinished())
        {
            //SerialCtrl.println("actionState == Moving & trajectory over");
            if(!(action.angle <= 360.f)) // -180 <= action.angle <= 180° pour être pris en compte, (normalement donc on met 360 au cas où)
            {
                navigator.turn_to(action.angle);
            }

            actionState = TURNING;
        }
        /*
        //le bloc ci-dessous se lance si on est avant le timer indiqué dans ActionList, ou si on est arrivé à destination/quasi destination 
        if ((fsmSupervisor.is_no_state_set() || !fsmSupervisor.is_switching_state())
            && ((timeToReachCoords(get_abs_x(), get_abs_y(), action.x,action.y) <= action.countdownState +1.1f) //car time toReachCoords >= 1 à tout moment
                || distance_squared(get_abs_x(), get_abs_y(), action.x,action.y) <= ADMITTED_POSITION_ERROR*ADMITTED_POSITION_ERROR))
        {
            SerialCtrl.println("actionState - fsmSueprvisor nextState ");
            fsmSupervisor.setNextState(action.state);
        } 
        */
    }

    else if(actionState == TURNING && navigator.isTrajectoryFinished())// && fsmSupervisor.is_no_state_set())
    {           
        SerialCtrl.println("actionState turning - fsm nextState ");
         fsmSupervisor.setNextState(action.state);
        //SerialCtrl.println("actionState - turning done");
        curActIndex++;
        actionState = BEGIN;
    } 
}

void update()
{ 
    Action curAction = curSection[curActIndex];
    //Une section : un ensemble d'actions, action_dispatcher s'occupe de voir ce qu'il doit faire avec une action ou passer à l'action suivante pour la prochaine loop
    if(curSection != NULL)
    {
       action_dispatcher(curAction);
    }
    if(curSection == NULL)
    {
        //TODO : changement de curSection, dans un ordre prédeterminé sauf si le chemin est occupé:
        /*
        Recup ecueil 
        phare
        Dépose ecueil
        Récup ecueil
        Manche à air
        dépose écueil

        Si plus rien à faire : rentrer à la base/circuit d'attente
        */
    }
    if((millis()-start_millis > timer*1000-5000) & !moveBackToBase)
    {
        moveBackToBase = true;
        //set_current_action(*(compute_final_point()));
    }
    if(millis()-start_millis > timer*1000-5000) // -5000 : hardcode du pavillon qui doit se déclencher à 5s de la fin
    {
        ActuatorSupervisor::deploy_pav();

    }
    //->passer à l'etat suivant si le fsm est à un état "final", càd sans état supplémentaire prévue par défaut
    //Par exemple, pour le récupérage de gobelet, on doit rester longtemps dans l'état, donc jusqu'à ce qu'il soit dans "deadState", on attends

}


void set_current_action(Action *action)
{
    curSection = action;
}

//to be called when receveing information from raspberry about girouette in communication.h
void compute_final_point(bool isGirouetteWhite) 
//White : Sud, Black : Nord
{
    float theta = 0.f;

    if(isStartingLeft)
    {
        ActionList::GetToFinal[0].x = 200.f;
        ActionList::GetToFinal[0].y = (isGirouetteWhite) ? 500.f : 1500.f;
        ActionList::GetToFinal[0].angle = 0.0f;
    }
    else
    {
        ActionList::GetToFinal[0].x = 2800.f;
        ActionList::GetToFinal[0].y = (isGirouetteWhite) ? 500.f : 1500.f;
        ActionList::GetToFinal[0].angle = 0.0f;
    }
}

void addScore(int add)
{
    score += add;
}
/* méthodes à rajouter :
Temps estimé pour réaliser action
(Heuristique action/temps réalsier une action)

externes : 
setArrivalCoordinate() ->comm.cpp pour arriver à bon port

(freeEcocup() -> comm.cpp pour autoriser d'autres coords ??)

*/




} // namespace MatchDirector
