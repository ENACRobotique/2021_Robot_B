#include "MoveServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "../actuatorSupervisor.h"

MoveServo::MoveServo(ActuatorSupervisor::CupColor color, bool isFront, bool isDeploying) {
    SerialDebug.println("deploying servo");
    time_start = 0;
}

void MoveServo::initiate_mvt(ActuatorSupervisor::CupColor color, bool isFront, bool isDeploying) { 
    //isFront = false => back, isDeployed = false => retract
    time_start = millis();
    int begin = (isFront) ? 0 : 3;
    int end = (isFront) ? 3 : 5;
    for (int i = begin; i < end; i++)
    {
        if(color == ActuatorSupervisor::CupColor::NONE || 
            color == ActuatorSupervisor::get_color(i))
        {
            int angle = (isDeploying) ? SERVO_ANGLE_DEPLOYED : SERVO_ANGLE_RETRACTED;
            ActuatorSupervisor::armServos[i].moveServo(angle);
            ActuatorSupervisor::switch_ev(false, i);
            ActuatorSupervisor::switch_pompe(true, i);
        }
    }
}

void MoveServo::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(NULL);
	} 
}

void MoveServo::leave() {

    SerialDebug.println("Leaving Deployment of Servo");
}

