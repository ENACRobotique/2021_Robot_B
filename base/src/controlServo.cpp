#include "controlServo.h"
#include "Arduino.h"
#include "PWMServo.h"
#include "Wire.h"
#include "params.h"

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  515 // This is the 'maximum' pulse length count (out of 4096)
#define FACTOR (SERVOMAX - SERVOMIN)/180 // Facteur de convertion de degrés en pulselength
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define NB_SERVO 8

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