/*
 * params.h
 *
 *  Created on: 18 mars 2018
 *      Author: elie
 */

<<<<<<< HEAD

#ifndef PARAMS_H_
#define PARAMS_H_

#define VOLT_TO_DIST(volt) (13 * pow (volt  * 0.0048828125, -1)) 
#define DEBUG_MATCH_DIRECTOR
//#define DEBUG_ODOMETRY

#ifndef DEBUG_NO_ARDUINO
    #include "Arduino.h"


    // 

    // ** Serials ports ** //
    //#define SerialDebug = Serial;
    //#define SerialCtrl = Serial5;
    //(using stream instead of HardwareSerial because Serial doesn't inherit it)
    static Stream& SerialDebug = Serial; // used for debug printing - Serial1 -> USB   
    static HardwareSerial& SerialCtrl = Serial2; //used for Xbee, sending and receiveing remotly instructions, remote debug
    static HardwareSerial& SerialLidar = Serial1;
#endif
=======
#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"


#define VOLT_TO_DIST(volt) (13 * pow (volt  * 0.0048828125, -1)) 

// #define DEBUG_ODOMETRY

// ** Serials ports ** //

//#define SerialDebug = Serial;
//#define SerialCtrl = Serial5;
//(using stream instead of HardwareSerial because Serial doesn't inherit it)
static Stream& SerialDebug = Serial; // used for debug printing - Serial1 -> USB   
static HardwareSerial& SerialCtrl = Serial2; //used for Xbee, sending and receiveing remotly instructions, remote debug
static HardwareSerial& SerialLidar = Serial1;
>>>>>>> lidar_et_pathfinding

const int ARUCO_ID = 1;

const unsigned long TIME_RACE = 100000;

<<<<<<< HEAD
#pragma region pins physiques
=======
>>>>>>> lidar_et_pathfinding

const int MOT_ENCODEUR1_A = 21;
const int MOT_ENCODEUR1_B = 20;
const int MOT_ENCODEUR2_A = 23;
const int MOT_ENCODEUR2_B = 22;

<<<<<<< HEAD
const int WHEEL_ENCODEUR1_A = 16;//16;
const int WHEEL_ENCODEUR1_B = 17;//17;
const int WHEEL_ENCODEUR2_A = 29;//29;
const int WHEEL_ENCODEUR2_B = 30;//30;
=======
const int WHEEL_ENCODEUR1_A = 21;//16;
const int WHEEL_ENCODEUR1_B = 20;//17;
const int WHEEL_ENCODEUR2_A = 23;//29;
const int WHEEL_ENCODEUR2_B = 22;//30;
>>>>>>> lidar_et_pathfinding


const int MOT1_PWM = 35;//36;
const int MOT1_DIR = 34;//33;
const int MOT2_PWM = 36;//35;
const int MOT2_DIR = 33;//34;

//const int BATT_CHARGE = 37;

const int SERVO_PAV = 37;
const int SERVO_BAR = 38;

//PCA 9685PW - not pin from teensy !
const int EV5 = 14; //EV = ElectroVanne
const int EV4 = 13;
const int EV3 = 12;
const int EV2 = 11;
const int EV1 = 10;
const int POMPE5 = 9;
const int POMPE4 = 8;
const int POMPE3 = 7;
const int POMPE2 = 6;
const int POMPE1 = 5;
const int SERVO5 = 4;
const int SERVO4 = 3;
const int SERVO3 = 2;
const int SERVO2 = 1;
const int SERVO1 = 0;

//Pins from I2C multiplexer, not from teensy :
const int COLOR_SENSOR_1 = 0;//TODO

const int MOT_LIDAR = 2;
const int COLOR = 25;
const int TIRETTE = 24;
const int DISPLAY1 = 7;
const int DISPLAY2 = 8;

<<<<<<< HEAD
#pragma endregion 

#pragma region addresses I2C et params driver de led
const int LED_DRIVER_ADDRESS = 0x46; //0x46 is configured, 0x70 is "all called led address" (don't use it )
const int PWM_FREQUENCY = 50;
#pragma endregion

const float SPEED_MAX = 500.0f; //0.5f;
const float OMEGA_MAX = 1.4f;

=======
const float SPEED_MAX = 500.0f; //0.5f;
const float OMEGA_MAX = 1.4f;

// const int SPARE1 = 10;
// const int SPARE2 = 9;
// const int SPARE3 = 8;
// const int SPARE4 = 7;

// const int DYNAMIXEL_CONTROL = 30;
// const int DYNAMIXEL_ID =1;
>>>>>>> lidar_et_pathfinding

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

<<<<<<< HEAD
const float ADMITTED_POSITION_ERROR = 5; //3
=======
const float ADMITTED_POSITION_ERROR = 3; //5
>>>>>>> lidar_et_pathfinding
const float ADMITTED_ANGLE_ERROR = 0.01;

//const float MAX_DRIFT = 0.1;
//const float WHEEL_DIAMETER = 55.0;
<<<<<<< HEAD
const float robot_center_x = 150.f; // largeur / 2
const float WHEELBASE = 169.;
const float INCR_TO_MM = 0.3414969475;   //PI*WHEEL_DIAMETER/805.12; ou divisé par 701 pour l'encodeur des moteurs 12V
const float INCR_TO_MM_1 = INCR_TO_MM * 1;
const float INCR_TO_MM_2 = INCR_TO_MM * 1;
const float CODER_WHEEL_BASE = 222.;
const float CODER_INCR_TO_MM = 0.061359232;   //PI*WHEEL_DIAMETER/805.12; ou divisé par 701 pour l'encodeur des moteurs 12V
const float CODER_INCR_TO_MM_1 = CODER_INCR_TO_MM * 1;
const float CODER_INCR_TO_MM_2 = CODER_INCR_TO_MM * 1;
=======
const float WHEELBASE = 169.;
const float INCR_TO_MM = 0.3414969475;   //PI*WHEEL_DIAMETER/805.12; ou divisé par 701 pour l'encodeur des moteurs 12V
const float INCR_TO_MM_1 = INCR_TO_MM * 1; //0.15608071609
const float INCR_TO_MM_2 = INCR_TO_MM * 1;
>>>>>>> lidar_et_pathfinding
//const float INCR_TO_TOURS = 1/805.12;
const float CONTROL_PERIOD = 0.02;
const float NAVIGATOR_PERIOD = 0.05;
const float COMMUNICATION_PERIOD = 0.1;
const float STATE_PERIOD = 0.1;

const unsigned long THROW_DURATION = 20000;
const unsigned long SERVO_MOVEMENT_DURATION = 1000;
const unsigned long DETECTION_STOP_TIME = 1500;

<<<<<<< HEAD
=======
const int GREEN = 1;
const int ORANGE = !GREEN;
const int PURPLE = 1;
const int YELLOW = !PURPLE;
>>>>>>> lidar_et_pathfinding


enum sensors {IR1=33,IR2,IR3,IR4,IR5,IR6,IR_test};
const sensors IR_sel=IR_test;


//params de capture ecocup
const float dist_min=5,dist_max=20;//valeurs initial turn
const float delta_step_forward=20;//mm
const float nominal_delta_rot=10;//degres
const float dist_opt=4.5;

<<<<<<< HEAD
//ARMS : 
const int SERVO_ANGLE_RETRACTED = 150;
const int SERVO_ANGLE_DEPLOYED = 60;

//servos : 
const int SERVO_PAV_ANGLE_RTRCTED = 15;
const int SERVO_PAV_ANGLE_DPLOYED = 105;

const int SERVO_BAR_ANGLE_RTRCTED = 0;
const int SERVO_BAR_ANGLE_DPLOYED = 130;

=======
const int SERVO_ANGLE_RETRACTED = 150;
const int SERVO_ANGLE_DEPLOYED = 60;

>>>>>>> lidar_et_pathfinding
// const int NB_US = 4;
#endif /* PARAMS_H_ */
