#include <iostream>
#include "Action.h"
#include "ActionsList.h"
#include "../base/src/params.h"
#include "../base/src/navigator.h" 
#include "../base/src/FsmSupervisor.h" 

    using namespace std;
   int main()
   {
    cout << "Hello World" << endl;
    system("PAUSE");
    return 0;
   }

namespace MatchDirector
{

/*Control navigator (which is the high level interface to move the robot/give it a certain orientation) 
and FSM (which controls various actuators & execute codes depending on various states) 
depending on the time left & an order of action. 
Manage the score total, the score of an action is stored in Action. 
Can be modified by states if needed (for example, if an action is interacting with a variable amount of object & the score depend on this amount).
*/
    float timer = 100; // en s
    int score = 0;
    float init_x;
    float init_y;

    /* code à changer si on se foire sur le montage des roues */
    float offsetX = 0;
    float offsetY = 0;
    bool inverseX = false;
    bool inverseY = false;

void init()
{
    //TODO : call only when match has started;
    //TODO : implement timer count;
    bool isStartingLeft = true;
    if(isStartingLeft)
    {
        init_x = 0; //TODO : prendre en compte offset/inverse X??
        init_y = 1000;
        offsetY = 1000;
    }
    else
    {
        init_x = 2000; //TODO : prendre en compte offset/inverse X??
        init_y = 1000;
    }

}

void update()
{
    Action currentAction[10];
    int curActIndex = 0;
    //if(abs(currentAction[curActIndex].x - getTableCoordinateX() < 3 && pareil pour Y )
        //Aller à l'angle voulue
        //switcher à l'état si pas déjà fait
        // voir si on est dans un état"mort"
            //Si oui, curActIndex ++,
            //sinon attendre
    //->passer à l'etat suivant si le fsm est à un état "final", càd sans état supplémentaire prévue par défaut
    //Par exemple, pour le récupérage de gobelet, on doit rester longtemps dans l'état, donc jusqu'à ce qu'il soit dans "deadState", on attends

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


Actions : 
Ctrl Navigator
Ctrl FSM


} // namespace MatchDirector
