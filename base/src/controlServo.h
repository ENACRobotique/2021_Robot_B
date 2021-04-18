#ifndef CONTROLSERVO_H_
#define CONTROLSERVO_H_

#include "Arduino.h"
#include "PWMServo.h"

/* allow an interface with one servo 
they are stored in actuatorSupervisor
*/
class ControlServo{    
public:
    ControlServo();
    virtual ~ControlServo();
    void defInitAngle(int angle);
    void init(int ServoPIN);
    void moveServo(int angle); //input a delta angle
    void resetPos();
    int returnPos();
    PWMServo servo;
private:
   int init_angle = 0;
};

#endif