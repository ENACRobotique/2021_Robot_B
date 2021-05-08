#include <iostream>
#include "math.h"
#include "Action.h"
#include "ActionsList.h"
#include "../base/src/params.h"
#include "../base/src/navigator.h" 
#include "../base/src/odometry.h"" 
#include "../base/src/FsmSupervisor.h" 
;

    using namespace std;
   int main()
   {
    cout << "Hello World" << endl;
    MatchDirector::init();
    system("PAUSE");
        cout << "init done" << endl;
        MatchDirector::update();
            system("PAUSE");

   }

namespace MatchDirector
{

/*Control navigator (which is the high level interface to move the robot/give it a certain orientation) 
and FSM (which controls various actuators & execute codes depending on various states) 
depending on the time left & an order of action. 
Manage the score total, the score of an action is stored in Action. 
Can be modified by states if needed (for example, if an action is interacting with a variable amount of object & the score depend on this amount).
*/

    bool isStartingLeft = true;
    bool isDrivingBackward = true; //if move with navigator with positive number, robot goes backward

    Action *curSection = NULL; // undefined size of array
    //Section = multiple actions that usually lead to points at the end
    int curActIndex = 0;
    ActionState actionState = BEGIN;

    float timer = 100; // en s
    int score = 0;
    float offsetX = 0; //offsets au début du terrain par rapport à l'abs
    float offsetY = 0;

void init()
{
    //TODO : call only when match has started;
    //TODO : implement timer count;

    /* en fonction de la taille du terrain */
    offsetY = 1000; //largeur terrain/2
    offsetX = (isStartingLeft) ? robot_center_x : (3000 - robot_center_x); //3000-> longueur terrain
    //DEBUG : 
    //curSection = EcocupsTopLeft;
}

void update()
{
    Action curAction = curSection[curActIndex];
    if(actionState == BEGIN)
    {
        abs_coords_to(curAction.x,curAction.y);
        actionState = MOVING;
    }
    else if(actionState == MOVING && 
    timeToReachCoords(get_abs_x(), get_abs_y(), curAction.x,curAction.y) <= curAction.countdownState)
    {
        fsmSupervisor.setNextState(curAction.state);
    }
    else if(actionState == MOVING && navigator.isTrajectoryFinished()) //Has moved -> has turned
    {
        navigator.turn_to(curAction.angle);
        actionState = TURNING;
    }
    else if(actionState == TURNING && navigator.isTrajectoryFinished() && fsmSupervisor.is_no_state_set())
    {
        curActIndex++;
        actionState = BEGIN;
    }
    //->passer à l'etat suivant si le fsm est à un état "final", càd sans état supplémentaire prévue par défaut
    //Par exemple, pour le récupérage de gobelet, on doit rester longtemps dans l'état, donc jusqu'à ce qu'il soit dans "deadState", on attends

}

void abs_coords_to(float x, float y)
{  
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        navigator.move_to(-x + offsetX, -y + offsetY);
    }
    else
    {
        navigator.move_to(x + offsetX, y + offsetY);
    }
    
}

float get_abs_x()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -Odometry::get_pos_x() + offsetX;
    }
    else 
    {
        return Odometry::get_pos_x() + offsetX;
    }
}

float get_abs_y()
{
    if((!isStartingLeft && !isDrivingBackward) || (isStartingLeft && isDrivingBackward))
    {
        return -Odometry::get_pos_y() + offsetY;
    }
    else 
    {
        return Odometry::get_pos_y() + offsetY;
    }
}
float timeToReachCoords(float begX, float begY, float targetX, float targetY)
{
    float time = 0;
    float d_squared = (targetX-begX)*(targetX-begX)+(begY-targetY)*(targetX-begX);
    if(d_squared >= ACCEL_MAX*ACCEL_MAX)
    {
         time = d_squared/(ACCEL_MAX*ACCEL_MAX); //trapèze de vitesse majorée
    }
    else
    {
        float distance = sqrt((targetX-begX)*(targetX-begX)+(begY-targetY)*(targetX-begX));
    //t = d/v
        ACCEL_MAX ;
        time = 4;//TODO trouver une meilleure formule, avec temps accelerer, décellérer, temps pour tourner
    }
    return time;

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
