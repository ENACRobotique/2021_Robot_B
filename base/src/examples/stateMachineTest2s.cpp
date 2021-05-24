#include "stateMachineTest2s.h"
#include "arduino.h"
#include "FsmSupervisor.h"
#include "../stateMachine/recalibration_wall.h"

bool hasStarted = false;

//actuellement on teste une recalibration sur le mur de départ, donc ne pas coller le robot au mur !
void stateMachineTest2s::init() {
    
}

void stateMachineTest2s::update() {
    if(millis() > 2000.0f)
    {
        fsmSupervisor.setNextState(&Recalibration_wall(0, 0, true));
    }
}
