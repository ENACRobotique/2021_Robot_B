#include "MoveBar.h"
#include "etat_begin.h"
#include "../actuatorSupervisor.h"
#include "params.h"
#include "FsmSupervisor.h"


MoveBar::MoveBar(bool isDeployed) {
    this->isDeploying = isDeploying;
}

void MoveBar::enter() {
    if(isDeploying)
    {
        ActuatorSupervisor::deploy_bar();
    }
    else
    {
        ActuatorSupervisor::retract_bar();
    }
    

}

void MoveBar::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(&etat_begin);
	} 
}

void MoveBar::leave() {
    SerialDebug.println("Leaving Deployment of Servo Pavillon");
}
