#include "MatchDirector.h"
#include "math.h"
#include "ActionsList.h"
#include "../params.h"
#include "../navigator.h" 
#include "../Odometry.h"
#include "../FsmSupervisor.h" 
#include "../actuatorSupervisor.h"
#include "Arduino.h" //NULL definition
#include "utils.h"

namespace MatchDirector
{

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
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        navigator.move_to(-x + offsetX, -y - offsetY);
    }
    else
    {
        navigator.move_to(x - offsetX, y - offsetY);
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

void update()
{ 
    Action curAction = curSection[curActIndex];
    
    if(curSection != NULL)
    {
        if(actionState == BEGIN)
        {
            SerialCtrl.println("actionState == begin");
            abs_coords_to(curAction.x,curAction.y);
            actionState = MOVING;
        }

        else if(actionState == MOVING && 
            ((timeToReachCoords(get_abs_x(), get_abs_y(), curAction.x,curAction.y) <= curAction.countdownState +1.1f) //car time toReachCoords >= 1 à tout moment
                || distance_squared(get_abs_x(), get_abs_y(), curAction.x,curAction.y) <= ADMITTED_POSITION_ERROR*ADMITTED_POSITION_ERROR)) 
        {
            SerialCtrl.println("actionState == execute state");
            fsmSupervisor.setNextState(curAction.state);
        }
        else if(actionState == MOVING && navigator.isTrajectoryFinished()) //Has moved -> has turned
        {
                        SerialCtrl.println("actionState == Moving & trajectory over");
            navigator.turn_to(curAction.angle);
            actionState = TURNING;
        }
        else if(actionState == TURNING && navigator.isTrajectoryFinished() && fsmSupervisor.is_no_state_set())
        {
                        SerialCtrl.println("actionState == turning");
            curActIndex++;
            actionState = BEGIN;
        } 
    }
    if((millis()-start_millis > timer*1000-5000) & !moveBackToBase)
    {
        moveBackToBase = true;
        //set_current_action(*(get_to_final()));
    }
    if(millis()-start_millis > timer*1000-5000) // -5000 : hardcode du pavillon qui doit se déclencher à 5s de la fin
    {
        SerialDebug.println("déploiement du pavillon matchDirector");
        ActuatorSupervisor::deploy_pav();

    }
    //->passer à l'etat suivant si le fsm est à un état "final", càd sans état supplémentaire prévue par défaut
    //Par exemple, pour le récupérage de gobelet, on doit rester longtemps dans l'état, donc jusqu'à ce qu'il soit dans "deadState", on attends

}


void set_current_action(Action *action)
{
    curSection = action;
}

Action* get_to_final(bool isGirouetteWhite)
{
    //float x = (isGirouetteWhite) ?, aussi prendre en compte gauche ou droite
    //Find/calculate destination coordinate
    Action* GetToFinal = new Action[10];
    GetToFinal =
    {
        //{x,y, 0.0f, &no_state, 5.f},
    };
    return GetToFinal;
}


/* méthodes à rajouter :
Temps estimé pour réaliser action
(Heuristique action/temps réalsier une action)

externes : 
setArrivalCoordinate() ->comm.cpp pour arriver à bon port
addScore()
(freeEcocup() -> comm.cpp pour autoriser d'autres coords ??)

*/




} // namespace MatchDirector
