#include "DeployServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "../actuatorSupervisor.h"

DeployServo::DeployServo() {
    SerialDebug.println("deploying servo");
    time_start = 0;
}

void DeployServo::initiate_mvt(ActuatorSupervisor::CupColor color, bool isFront) {
    time_start = millis();
    int begin = (isFront) ? 0 : 3;
    int end = (isFront) ? 3 : 5;
    for (int i = begin; i < end; i++)
    {
        if(color == ActuatorSupervisor::CupColor::NONE || 
            color == ActuatorSupervisor::get_color(i))
        {
            ActuatorSupervisor::armServos[i].moveServo(SERVO_ANGLE_DEPLOYED);
            ActuatorSupervisor::switch_ev(false, i);
            ActuatorSupervisor::switch_pompe(true, i);
        }
    }
}

void DeployServo::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(NULL);
	} 
}

void DeployServo::leave() {

    SerialDebug.println("Leaving Deployment of Servo");
}

