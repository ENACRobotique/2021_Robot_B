#include "Arduino.h"
#include "params.h"
#include "controlServo.h"

namespace ActuatorSupervisor
{
    //front : 
	ControlServo servo1;
	ControlServo servo2;
	ControlServo servo3;

    void init()
    {
        servo1.defInitAngle(150);
        servo1.init(SERVO1);
        //TODO : define other servos
    }

    void FrontDeployServo()
    {
        servo1.moveServo(60);
        digitalWrite(POMPE, HIGH);
        digitalWrite(VANN, LOW);
        //actionner pompe à air
    }

    void FrontRetractServo()
    {
        servo1.moveServo(150);
    }

    void FrontReleaseVann()
    {
        digitalWrite(VANN, HIGH);
        digitalWrite(POMPE, LOW);
    }



}