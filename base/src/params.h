/*
 * params.h
 *
 *  Created on: 18 mars 2018
 *      Author: elie
 */

#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"


#define VOLT_TO_DIST(volt) (13 * pow (volt  * 0.0048828125, -1)) 

// #define DEBUG_ODOMETRY
#define IHM

// ** Serials ports ** //

//#define SerialDebug = Serial;
//#define SerialCtrl = Serial5;
//(using stream instead of HardwareSerial because Serial doesn't inherit it)
static Stream& SerialDebug = Serial; // used for debug printing - Serial1 -> USB   
static HardwareSerial& SerialCtrl = Serial2; //used for Xbee, sending and receiveing remotly instructions, remote debug


const int ARUCO_ID = 1;

const unsigned long TIME_RACE = 100000;

//MC2 A : 23 MC2 B : 22
//MC1 A : 21 MC1 B : 20
//COD 2 A : 29 COD2B : 30
//
const int MOT_ENCODEUR1_A = 21;//21; 23;
const int MOT_ENCODEUR1_B = 20;//20; 22;
const int MOT_ENCODEUR2_A = 23;//29;
const int MOT_ENCODEUR2_B = 22;//30;

const int WHEEL_ENCODEUR1_A = 21;//16;
const int WHEEL_ENCODEUR1_B = 20;//17;
const int WHEEL_ENCODEUR2_A = 29;//23;//
const int WHEEL_ENCODEUR2_B = 30;//22;//


const int MOT1_PWM = 36;
const int MOT1_DIR = 33;
const int MOT2_PWM = 35;
const int MOT2_DIR = 34;

//const int BATT_CHARGE = 37;

// const int US_RANGE = 35;
// const int US_RANGE_DIMINUSHED = 25;

const int SERVO1 = 38; //BAR
// const int SERVO2 = 37; //Pavillon


const int POMPE = 15;
const int VANN = 14;
// const int MOT_GALET_L = 35;
// const int MOT_LIDAR = 35;

const int COLOR = 26;
const int TIRETTE = 25;

const float SPEED_MAX = 500.0f; //0.5f;
const float OMEGA_MAX = 1.4f;

// const int SPARE1 = 10;
// const int SPARE2 = 9;
// const int SPARE3 = 8;
// const int SPARE4 = 7;

// const int DYNAMIXEL_CONTROL = 30;
// const int DYNAMIXEL_ID =1;

const int EMERGENCY_BRAKE = 1800;
const int ACCEL_MAX = 500;
const int ACCEL_MAX_THROW = 100;
const int SPEED_MAX_CRUISE = 350;

const int ACCEL_MAX_CAP = 100;
const int SPEED_MAX_CAP = 100;

const float ACCEL_OMEGA_MAX_CRUISE = 1;
const float OMEGA_MAX_CRUISE = 1.5;

const float ACCEL_OMEGA_MAX_CAP = 0.3;
const float OMEGA_MAX_CAP = 0.5;

const float ACCEL_OMEGA_MAX = 1;


const float ADMITTED_OMEGA_ERROR = 0.03;
const float ADMITTED_SPEED_ERROR = 10;

const float ADMITTED_POSITION_ERROR = 3; //5
const float ADMITTED_ANGLE_ERROR = 0.01;

//const float MAX_DRIFT = 0.1;
//const float WHEEL_DIAMETER = 55.0;
const float WHEELBASE = 169.;
const float INCR_TO_MM = 1;   //PI*WHEEL_DIAMETER/805.12; ou divisé par 701 pour l'encodeur des moteurs 12V // 2048 pour les AMT-102V
const float INCR_TO_MM_1 = INCR_TO_MM * 0.3414969475; // 0.3414969475
const float INCR_TO_MM_2 = INCR_TO_MM * 0.3414969475;//INCR_TO_MM * 0.0613592315;
//const float INCR_TO_TOURS = 1/805.12;
const float CONTROL_PERIOD = 0.02;
const float NAVIGATOR_PERIOD = 0.05;
const float COMMUNICATION_PERIOD = 0.1;
const float STATE_PERIOD = 0.1;

const unsigned long THROW_DURATION = 20000;
const unsigned long SERVO_MOVEMENT_DURATION = 1000;
const unsigned long DETECTION_STOP_TIME = 1500;

const int GREEN = 1;
const int ORANGE = !GREEN;
const int PURPLE = 1;
const int YELLOW = !PURPLE;


enum sensors {IR1=33,IR2,IR3,IR4,IR5,IR6,IR_test};
const sensors IR_sel=IR_test;


//params de capture ecocup
const float dist_min=5,dist_max=20;//valeurs initial turn
const float delta_step_forward=20;//mm
const float nominal_delta_rot=10;//degres
const float dist_opt=4.5;

const int SERVO_ANGLE_RETRACTED = 150;
const int SERVO_ANGLE_DEPLOYED = 60;

// const int NB_US = 4;
#endif /* PARAMS_H_ */
