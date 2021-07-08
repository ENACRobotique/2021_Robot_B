#include "MatchDirector.h"
#include "math.h"
#include "ActionsList.h"
#include "../params.h"
#include "../navigator.h" 
#include "../odometry.h"
#include "../FsmSupervisor.h" 
#include "../actuatorSupervisor.h"
#include "../stateMachine/etat_begin.h"
#include "Arduino.h" //NULL definition
#include "utils.h"
#include "DisplayController.h"
#include "motorControl.h"

/**
 * @brief 
 * @file MatchDirector.cpp
 * @ingroup namespace

 */

/**
 * @brief Control navigator (which is the high level interface to move the robot/give it a certain orientation) 
and FSM (which controls various actuators & execute codes depending on various states) 
depending on the time left & an order of action. 
Manage the score total, the score of an action is stored in Action. 
Can be modified by states if needed (for example, if an action is interacting with a variable amount of object & the score depend on this amount).
 * 
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

    //ActionOrder actionOrder;
bool isGirouetteWhite = false;

    bool isStartingLeft = true;
    bool isDrivingBackward = false; //if move with navigator with positive number, robot goes backward
    bool isRobotStopped = false;
    Action *curSection = NULL; // undefined size of array
    //Section = multiple actions that usually lead to points at the end
    int curActIndex = 0;
    ActionState actionState = BEGIN;

    /**
     * @brief When there is a huge discrepancy between targeted position & position reached, this get reincremented and the same command is sent again
     *  @ingroup namespace
     */
    int nbReadjust = 0; //
    PointSeq curSeq;
    int curSeqIndex = 0;
    /**
     * @brief Number of time we can correct trajectory according to wheel encoder, in order not to be stuck trying to reach an unnatable precise position
     * 
     */
    bool hasStarted;


    int nbCorectionAuthorized = 0;
    float timer = 100; // en s, durée du match
    int score = 0;
    float offsetX = 0; //offsets au début du terrain par rapport à l'abs
    float offsetY = 0;
    uint32_t start_millis;
    bool moveBackToBase;
    /**
     * @brief Flag that is set depending if the activities is done in the 
     * 
     */
    int activitiesDoneFlag = 0; 

void init()
{
    start_millis =  3600000;
    hasStarted = false;
    moveBackToBase = false;
    //TODO : call only when match has started;
    //TODO : implement timer count;

    //en fonction de la taille du terrain 

    offsetY = (isStartingLeft) ? 1090.0f : 1315.f ; //largeur terrain/2
    offsetX = (isStartingLeft) ? robot_center_x : (3000.0f - robot_center_x); //3000-> longueur terrain
   
   ActionList::GetToFinal[0].x = (isStartingLeft) ? 250.f:2750.f;
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
    navigator.move_to(abs_x_to_local(x), abs_y_to_local(y));
    
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
float get_abs_wheel_x()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -odometry_wheel.get_pos_x() + offsetX;
    }
    else 
    {
        return odometry_wheel.get_pos_x() + offsetX;
    }
}

float get_abs_wheel_y()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -odometry_wheel.get_pos_y() + offsetY;
    }
    else 
    {
        return odometry_wheel.get_pos_y() + offsetY;
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
    float full_pos[3] = {get_abs_x(), get_abs_y(), odometry_wheel.get_pos_theta()};
    /*
    SerialCtrl.println("debug 1");
    SerialCtrl.println(actionState == BEGIN);
    SerialCtrl.println(fsmSupervisor.is_no_state_set());
    SerialCtrl.println(navigator.isTrajectoryFinished());
    SerialCtrl.println("debug 2");
    */
    //start only when fsmSupervisor has no state
    if(actionState == BEGIN && fsmSupervisor.is_no_state_set() && navigator.isTrajectoryFinished())
    {
        SerialCtrl.print("new action :");
        SerialCtrl.print("\t");
        SerialCtrl.print(action.x);
        SerialCtrl.print("\t");
        SerialCtrl.print(action.y);
        SerialCtrl.print("\t");
        SerialCtrl.println(action.angle);
        //SerialCtrl.println("actionState == begin");
       
        if(ATC::proximity_check(&ATC::lidar, true, full_pos) && false)
        {
            /*
            for (int i = 0; i < 360; i++)
            {
                if(ATC::lidar.get_distance(i) != 0)
                {
                    SerialCtrl.print("angle : ");
                    SerialCtrl.print(i);
                            SerialCtrl.print(" distance : ");
                    SerialCtrl.println(ATC::lidar.get_distance(i));
                }
            }
            */
            SerialCtrl.println("path is BLOCKEd ! WAITING 2! ");
        }
        else if(action.x >= -100.f && action.y >= -100.f)
        {
            SerialCtrl.println("chemin direct !");
            abs_coords_to(action.x,action.y);
            actionState = MOVING;
        }
        
    }

    else if(actionState == MOVING)
    {
        if (navigator.isTrajectoryFinished())
        {
            // Si on est pas suffisament proche de la position et qu'on a le droit de se réajuster (permission lié à un "timeout" pour pas perdre trop de tps à se réajuster)
            if (distance_squared(get_abs_x(), get_abs_y(), action.x,action.y) > ADMITTED_POSITION_ERROR*ADMITTED_POSITION_ERROR
                && nbReadjust < nbCorectionAuthorized / 2) // on divise par 2 pour laiser la moitié de corrections autorisés à la correction d'angle
            {
                SerialCtrl.println("reajustement position car erreur trop grande (réel vs erreur admise): ");
                nbReadjust++;
            }
            else
            {
                if(!(action.angle <= -360.f)) // -180 <= action.angle <= 180° pour être pris en compte, (normalement donc on met 360 au cas où)
                {
                    SerialCtrl.print("turning to angle : ");
                    SerialCtrl.println(action.angle);
                    navigator.turn_to(action.angle);
                }
                actionState = TURNING;
                SerialCtrl.println("turning");
            }

        }
    }

    else if(actionState == TURNING && navigator.isTrajectoryFinished())// && fsmSupervisor.is_no_state_set())
    {          

        if(abs(action.angle-odometry_wheel.get_pos_theta()) > ADMITTED_DEG_ANGLE_ERROR && nbReadjust < nbCorectionAuthorized)
        {
            SerialCtrl.println("reajustement angle");
            SerialCtrl.println(odometry_wheel.get_pos_theta());
            nbReadjust++;
            actionState = MOVING;
        }

        SerialCtrl.print("odometry wheel pos: ");
        SerialCtrl.print(get_abs_wheel_x());
        SerialCtrl.print("\t");
        SerialCtrl.print(get_abs_wheel_y());
        SerialCtrl.print("\t");
        SerialCtrl.println(odometry_wheel.get_pos_theta());
        //SerialCtrl.println(navigator.theta_target);
        SerialCtrl.print("real pos : ");
        SerialCtrl.print(get_abs_x());
        SerialCtrl.print("\t");
        SerialCtrl.println(get_abs_y());
        SerialCtrl.print("\t");
        SerialCtrl.println(odometry_motor.get_pos_theta());
        fsmSupervisor.setNextState(action.state);
        //SerialCtrl.println("actionState - turning done");
        curActIndex++;
        //curSeqIndex = -1;
        nbReadjust = 0;
        actionState = BEGIN;

    } 
}

void update()
{ 
    if(hasStarted && start_millis == 3600000)
    {

        start_millis = millis();
        displayController.setNbDisplayed(0);
    }
    Action curAction = curSection[curActIndex];
    //Une section : un ensemble d'actions, action_dispatcher s'occupe de voir ce qu'il doit faire avec une action ou passer à l'action suivante pour la prochaine loop
    if(curSection != NULL && !ActionList::isNull(&curAction) && !isRobotStopped)
    {
       action_dispatcher(curAction);
    }
    // remplacer avec un else if pas de retoru à la base vu le temps restant
    /*
    if(curSection == NULL || ActionList::isNull(&curAction))
    {
        SerialCtrl.println("curSection is null or curAction is invalid !");

        //TODO : changement de curSection, dans un ordre prédeterminé sauf si le chemin est occupé:
        /*
        Recup ecueil 
        phare
        Dépose ecueil
        Récup ecueil
        Manche à air
        dépose écueil

        Checker si la zone est dispo, sinon faire autre chose
        Si rien n'est dispo : attendre

        Si plus rien à faire : rentrer à la base/circuit d'attente
        Si temps pressant (< 30s), on rentre à la base
            
        */
    //}
    
    if((millis()-start_millis > timer*1000-20000) && (millis()-start_millis< timer*1000-3000) && !moveBackToBase && hasStarted && !isRobotStopped) //20s avant !
    {
        SerialCtrl.print("returning to base ! ");
        moveBackToBase = true;
        //addScore(20);
        addScore(6);
        compute_final_point();
    }
    if((millis()-start_millis > timer*1000-2000) && hasStarted) //20s avant !
    {
        SerialCtrl.print("final stop initiated : 2s left !  ");
        moveBackToBase = false;
        navigator.forceStop();
        set_current_action(&ActionList::NullAction);
       
        analogWrite(MOT1_PWM, 0);
		analogWrite(MOT2_PWM, 0);
        for(;;);
    }
    if(millis()-start_millis > timer*1000-5000 && hasStarted) // -5000 : hardcode du pavillon qui doit se déclencher à 5s de la fin
    {
        ActuatorSupervisor::deploy_pav();

    }
    //->passer à l'etat suivant si le fsm est à un état "final", càd sans état supplémentaire prévue par défaut
    //Par exemple, pour le récupérage de gobelet, on doit rester longtemps dans l'état, donc jusqu'à ce qu'il soit dans "deadState", on attends

}


void set_current_action(Action *action)
{
    curSection = action;
    fsmSupervisor.setNextState(&etat_begin);
    actionState = BEGIN;
    curActIndex = 0;
    curSeqIndex = 0;
    nbReadjust = 0;
    navigator.forceStop();
    SerialCtrl.println("new section set !");
}

//to be called when receveing information from raspberry about girouette in communication.h
void compute_final_point() 
//White : Sud, Black : Nord
{

ActionList::GetToFinal[2];
    float theta = 0.f;

    if(isStartingLeft)
    {
        if(isGirouetteWhite) //sud
        {
            if(curSection == NULL)
            {
                set_current_action(ActionList::GetToFinalLeftHoldingSouth);
                            SerialCtrl.println("4");
            }
            else
            {
                set_current_action(ActionList::GetToFinalLeftEnRouteSouth);
                            SerialCtrl.println("5");
            }
        }
        else // nord
        {
            if(curSection == NULL)
            {
                set_current_action(ActionList::GetToFinalLeftHoldingNorth);
                SerialCtrl.println("6");
            }
            else
            {
                set_current_action(ActionList::GetToFinalLeftEnRouteNorth);
                            SerialCtrl.println("7");
            }
        }
    }
    else
    {

        if(isGirouetteWhite) //sud
        {
            if(curSection == NULL)
            {
                set_current_action(ActionList::GetToFinalRightHoldingSouth);
                            SerialCtrl.println("8");
            }
            else
            {
                set_current_action(ActionList::GetToFinalRightEnRouteSouth);
                            SerialCtrl.println("9");
            }
        }
        else
        {
            if(curSection == NULL)
            {
                set_current_action(ActionList::GetToFinalRightHoldingNorth);
                            SerialCtrl.println("10");
            }
            else
            {
                set_current_action(ActionList::GetToFinalRightEnRouteNorth);
                            SerialCtrl.println("11");
            }
        }
    } 

    /*
ActionList::GetToFinal[0].x = 200.f;
        ActionList::GetToFinal[0].y = (isGirouetteWhite) ? 800.f : 1600.f;
        ActionList::GetToFinal[0].angle = 0.0f;
    }
    */
   /*

           ActionList::GetToFinal[0].x = 2800.f;
        ActionList::GetToFinal[0].y = (isGirouetteWhite) ? 800.f : 1600.f;
        ActionList::GetToFinal[0].angle = 0.0f;

*/
    
}

void addScore(int add)
{
    score += add;
    displayController.setNbDisplayed(score);
}

PointSeq route_from_action(float actionX, float actionY)
{
        float entry[2] = {get_abs_x(), get_abs_y()};
        float exit[2] = {actionX, actionY};
        float robotPos[3] = {get_abs_x(), get_abs_y(), odometry_wheel.get_pos_theta()};
        return route_to_follow(entry, exit, robotPos);
}

PointSeq route_to_follow(float* entry, float* exit, float* robot_pos)
{
    Route route = ATC::find_route(&ATC::graph, entry, exit, &ATC::lidar, robot_pos);
    return ATC::read_route(route);
    //ATC::
}
/* méthodes à rajouter :
Temps estimé pour réaliser action
(Heuristique action/temps réalsier une action)

externes : 
setArrivalCoordinate() ->comm.cpp pour arriver à bon port

(freeEcocup() -> comm.cpp pour autoriser d'autres coords ??)

*/




} // namespace MatchDirector
