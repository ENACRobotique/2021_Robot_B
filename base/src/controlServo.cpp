#include "controlServo.h"
#include "Arduino.h"
#include "PWMServo.h"
#include "Wire.h"
#include "params.h"



//Don't forget to defInitAngle | TODO : refactor to definitangle in constructor
ControlServo::ControlServo(){

}

ControlServo::~ControlServo(){
}

void ControlServo::defInitAngle(int angle){

    init_angle = angle;
}

//if pwm = NULL -> will use teensy pins, if not -> use with pwm configured PCA 9685
void ControlServo::init(int ServoPIN, Adafruit_PWMServoDriver *pwm){ 
    if(pwm != NULL)
    {
        this->pin = ServoPIN;
        this->pwm = pwm;
        int pulselength = map(init_angle, 0, 180, SERVOMIN, SERVOMAX);
        (*pwm).setPWM(pin, 0, pulselength);
    }
    else
    {
        //servo.attach(ServoPIN);
        //servo.write(init_angle);
        //analogWrite(ServoPIN, 0); //equivalent of detach working
    }
    //delay(15);
}

void ControlServo::moveServo(int angle){
    if(pwm != NULL)
    {
        int pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
        (*pwm).setPWM(pin, 0, pulselength);
    }
    else
    {
        servo.write(angle);
    }

    //delay(15);
}

void ControlServo::resetPos(){
    servo.write(init_angle);
    delay(15);
}

int ControlServo::returnPos(){
    return(servo.read());
}