#ifndef CONTROLSERVO_H_
#define CONTROLSERVO_H_

#include "Arduino.h"
#include "PWMServo.h"
#include "Adafruit_PWMServoDriver.h"

#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600 
#define USMAX  2400
#define SERVO_FREQ 50

/* allow an interface with one servo 
they are stored in actuatorSupervisor
*/
class ControlServo{    
public:
    ControlServo();
    virtual ~ControlServo();
    void defInitAngle(int angle);
    void init(int ServoPIN, Adafruit_PWMServoDriver *pwm = NULL);
    void moveServo(int angle); //input a delta angle
    void resetPos();
    int returnPos();

protected:
    PWMServo servo;
    Adafruit_PWMServoDriver *pwm;
    int init_angle = 0;
    int pin;
};

#endif