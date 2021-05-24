#include "DeployPavillon.h"
#include "../actuatorSupervisor.h"
#include "../params.h"
#include "../FsmSupervisor.h"

DeployPavillon deployPavillon = DeployPavillon();

DeployPavillon::DeployPavillon() {
    time_start = 0;
}

void DeployPavillon::enter() {
    ActuatorSupervisor::armServos[0].moveServo(SERVO_PAV_ANGLE_DPLOYED);
    time_start = millis();
}

void DeployPavillon::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(NULL);
	} 
}

void DeployPavillon::leave() {
    
}
