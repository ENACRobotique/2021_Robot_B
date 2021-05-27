#include "Arduino.h"
#include "params.h"
#include "controlServo.h"
#include "actuatorSupervisor.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

namespace ActuatorSupervisor
{
	ControlServo armServos[5];
    ControlServo otherServos[2]; //[0] = Pavillon, [1] = tige horizontale

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(LED_DRIVER_ADDRESS, Wire);

    void init()
    {
        //arms servos
        /*
        for (int i = 0; i < 5; i++)
        {
            armServos[i].defInitAngle(150);
            armServos[i].init(servo_nb_to_pin(i), &pwm);
            switch_pompe(false, i);
            switch_ev(false, i);
        }
*/
        //other servos
        otherServos[0].defInitAngle(SERVO_PAV_ANGLE_RTRCTED);
        otherServos[0].init(SERVO_PAV, NULL); 
        otherServos[1].defInitAngle(SERVO_BAR_ANGLE_RTRCTED);
        otherServos[1].init(SERVO_BAR, NULL); 
        //TODO : pinMode nécessaire ou non
        //pinMode(POMPE, OUTPUT);
        //pinMode(VANN, OUTPUT);

        //multiplexers
        delay(10);
        //pwm.begin();
        //pwm.setPWMFreq(PWM_FREQUENCY);    
        SerialDebug.println("init done for actuatorSupervisor ! ");
    }

    void deploy_pav()
    {
        otherServos[0].moveServo(SERVO_PAV_ANGLE_DPLOYED);
    }
    void switch_pompe(bool isOn, int pompe)
    {
        SerialCtrl.println("ENABLE POMPE NOT TESTED");
        int start_pwm = (isOn) ? 4096 : 0;
        int end_pwm = (isOn) ? 0 : 4096;
        pwm.setPWM(pompe_nb_to_pin(pompe), start_pwm, end_pwm);
        //int pin = pompe_nb_to_pin(pompe);
    }
    void switch_ev(bool isOn, int ev)
    {
        SerialCtrl.println("ENABLE EV NOT TESTED");
        int start_pwm = (isOn) ? 4096 : 0;
        int end_pwm = (isOn) ? 0 : 4096;
        pwm.setPWM(pompe_nb_to_pin(ev), start_pwm, end_pwm);
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


/*

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");

  pwm.begin();
  pwm.setPWMFreq(1000);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

void loop() {
  // Drive each pin in a 'wave'
  for (uint8_t pin=0; pin<16; pin++) {
    pwm.setPWM(pin, 4096, 0);       // turns pin fully on
    delay(100);
    pwm.setPWM(pin, 0, 4096);       // turns pin fully off
  }
}

*/