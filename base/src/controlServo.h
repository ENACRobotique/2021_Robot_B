#ifndef CONTROLSERVO_H_
#define CONTROLSERVO_H_

#include "Arduino.h"
#include "PWMServo.h"
#include "Adafruit_PWMServoDriver.h"

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  515 // This is the 'maximum' pulse length count (out of 4096)
#define FACTOR (SERVOMAX - SERVOMIN)/180 // Facteur de convertion de degrés en pulselength
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define NB_SERVO 8

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