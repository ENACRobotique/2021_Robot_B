#include "stateMachineTest2s.h"
#include "Arduino.h"
#include "FsmSupervisor.h"
#include "../stateMachine/Recalibration_wall.h"


//actuellement on teste une recalibration sur le mur de départ, donc ne pas coller le robot au mur !
void stateMachineTest2s::init() {
    
}

void stateMachineTest2s::update() {
    if(millis() > 2000.0f)
    {
        fsmSupervisor.setNextState(&recalibration_wall_left);
    }
}
