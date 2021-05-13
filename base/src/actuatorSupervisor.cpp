#include "Arduino.h"
#include "params.h"
#include "controlServo.h"
#include "actuatorSupervisor.h"

namespace ActuatorSupervisor
{
	ControlServo armServos[5];

    void init()
    {
        for (int i = 0; i < 5; i++)
        {
            armServos[i].defInitAngle(150);
            armServos[i].init(servo_nb_to_pin(i));
            switch_pompe(false, i);
            switch_ev(false, i);
        }
        //TODO : pinMode nécessaire ou non
        //pinMode(POMPE, OUTPUT);
        //pinMode(VANN, OUTPUT);
        SerialCtrl.println("init done for actuatorSupervisor ! ");
    }
    /*
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
        //digitalWrite(VANN, HIGH);
        //digitalWrite(POMPE, LOW);
    } */
    void switch_pompe(bool isOn, int pompe)
    {
        SerialCtrl.println("ENABLE POMPE NOT IMPLEMENTED");
        //int pin = pompe_nb_to_pin(pompe);
    }
    void switch_ev(bool isOn, int ev)
    {
        SerialCtrl.println("ENABLE EV NOT IMPLEMENTED");
        //int pin = ev_nb_to_pin(ev);
    }
    int servo_nb_to_pin(int servo) 
    /* return 0 if servo_nb not between 0 & 4 included */
    {
        switch (servo)
        {
        case 0:
            return SERVO1;
        case 1:
            return SERVO2;
        case 2:
            return SERVO3;
        case 3:
            return SERVO4;
        case 4:
            return SERVO5;
        default:
            return 0;
        }
    }
    int pompe_nb_to_pin(int pompe) 
    /* return 0 if servo_nb not between 1 & 5 included */
    {
        switch (pompe)
        {
        case 0:
            return POMPE1;
        case 1:
            return POMPE2;
        case 2:
            return POMPE3;
        case 3:
            return POMPE4;
        case 4:
            return POMPE5;
        default:
            return 0;
        }
    }

    int ev_nb_to_pin(int ev) 
    /* return 0 if servo_nb not between 1 & 5 included */
    {
        switch (ev)
        {
        case 0:
            return EV1;
        case 1:
            return EV2;
        case 2:
            return EV3;
        case 3:
            return EV4;
        case 4:
            return EV5;
        default:
            return 0;
        }
    }

}
ActuatorSupervisor::CupColor ActuatorSupervisor::get_color(int sensor_nb) {
    SerialCtrl.println("get_color non implémenté !");
    return NONE;    
}
