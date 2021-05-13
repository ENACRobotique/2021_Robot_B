#include "Arduino.h"
#include "params.h"
#include "controlServo.h"

namespace ActuatorSupervisor
{
    //front : 
	ControlServo armServos[5];

    void init()
    {
        for (int i = 0; i < 5; i++)
        {
            armServos[i].defInitAngle(150);
            //armServos[i].init(SERVOPIN)
        }
        //TODO : faire ça pour toutes les pompes/vannes
        pinMode(POMPE, OUTPUT);
        pinMode(VANN, OUTPUT);
        SerialCtrl.println("init done for actuatorSupervisor ! ");
        //digitalWrite(POMPE, LOW);
        //digitalWrite(VANN, LOW);
        //analogWrite(A1, LOW);
        //analogWrite(A0, LOW);
    }
    void deploy_servo(int nb)
    {

    }
    void FrontDeployServo()
    {
        armServos[0].moveServo(60);
        //digitalWrite(POMPE, HIGH);
        //digitalWrite(VANN, LOW);
        //actionner pompe à air
    }

    void FrontRetractServo()
    {
        //servo1.moveServo(150);
    }

    void FrontReleaseVann()
    {
        digitalWrite(VANN, HIGH);
        digitalWrite(POMPE, LOW);
    }

    int servo_nb_to_pin(int servo) 
    /* return 0 if servo_nb not between 1 & 5 included */
    {
        switch (servo)
        {
        case 1:
            return SERVO1;
        case 2:
            return SERVO2;
        case 3:
            return SERVO3;
        case 4:
            return SERVO4;
        case 5:
            return SERVO5;
        default:
            return 0;
        }
    }



}