#include "MoveServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "../actuatorSupervisor.h"
#include "etat_begin.h"

MoveServo::MoveServo(CupColor color, bool isFront, bool isDeploying, bool isSucc) {
    //color = NONE => GREEN+RED, isFront = false => back, isDeployed = false => retract
    SerialDebug.println("instantiation of MoveServo done ! ");
    time_start = 0;
    this->color = color;
    this->isFront = isFront;
    this->isDeploying = isDeploying;
    this->isSucc = isSucc;

}

void MoveServo::enter()
{
    time_start = millis();
    int begin = (isFront) ? 0 : 3;
    int end = (isFront) ? 3 : 5;
    for (int i = begin; i < end; i++)
    {
        if(color == CupColor::NONE || color == ActuatorSupervisor::get_color(i))
        {
            int angle = (isDeploying) ? SERVO_ANGLE_DEPLOYED : SERVO_ANGLE_RETRACTED;
            ActuatorSupervisor::armServos[i].moveServo(angle);
            ActuatorSupervisor::switch_ev(false, i);
            ActuatorSupervisor::switch_pompe(!isSucc, i);
        }
    }
}

void MoveServo::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(&etat_begin);
	} 
}

void MoveServo::leave() {
    SerialDebug.println("Leaving Deployment of Servo");
}

