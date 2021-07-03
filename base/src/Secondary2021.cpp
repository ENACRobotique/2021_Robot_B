/**
 * @file Secondary2021.cpp
 * @author jonathan Muchler
 * @brief 
 * @date 2021-06-12
 * 
 * @image html vue_globale_code_2021.png "vue globale du code - au debut juin 2021"
 */

#include "Arduino.h" 
#include "odometry.h"
#include "motorControl.h" 
#include "params.h" 
#include "Metro.h"

#include "communication.h"
#include "navigator.h"
#include "FsmSupervisor.h"
#include "actuatorSupervisor.h"
#include "ai/MatchDirector.h"


#include "examples/servoTest.h" 
#include "examples/asservissementMoteur.h" 
#include "examples/debugTest.h" 
#include "examples/testXbee.h" 
#include "pathfinding.h"
#include "lidar/LidarData.h"
#include <lidar/RPLidar.h>
//#include "raspberryParser.h"
#include "DisplayController.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro debugLed = Metro(2000);
Metro navTime = Metro((unsigned long)(NAVIGATOR_PERIOD * 1000)); //2000
Metro TestTime = Metro((unsigned long)5000);
Metro commXBee = Metro((unsigned long)(COMMUNICATION_PERIOD * 1000));
Metro stateTime = Metro((unsigned long)(STATE_PERIOD * 1000));

float sp[4] = {0, 3.14f, 0, -3.14f};
int i = 0;

// RPLidar driver instance 
RPLidar rplidar;
// Lidar data container is initialised in pathfinding, as part of ATC namespace (not sure if good idea)

#define RPLIDAR_MOTOR 37 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 

#include "ai/ActionsList.h"
void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(11, OUTPUT);
  //testXbee::init();
    Serial2.begin(57600);
    Serial.begin(57600);
    //SerialDebug.begin(57600);
    SerialDebug.println("test SerialDebug 1");
    SerialCtrl.println("test SerialCtrl 1");
    //#ifdef DEBUG_ASSERVISSEMENT
      //Serial.println("cons_speed cons_omega actual_speed actual_omega");
    //#endif
    
    //while(!Serial) {} 
    /*
    Serial.println("initialization serialDebug");
    Serial.println("timer du match mis à 10s !!");
    SerialCtrl.println("initialization serialCtrl");
    */
  //Wire.begin();
  for(int i=0; i<10; i++) {
    SerialCtrl.println("starting...");
    delay(100);
  }

  // start lidar motor
  analogWrite(RPLIDAR_MOTOR, 200);
  // bind the RPLIDAR driver to the arduino hardware serial
  rplidar.begin(SerialLidar); //TODO: changer pour le bon canal serial
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  
  controlTime.reset();
	debugLed.reset();
	navTime.reset();
	TestTime.reset();
	odometry_motor.init();
  odometry_wheel.init();
	MotorControl::init();
  fsmSupervisor.init();
  ActuatorSupervisor::init();
  MatchDirector::init(); 

  //debugTest::scanSerial();
  //displayController.init();

  //while (!Serial);
  SerialCtrl.println("test serialctrl");
  Serial.println("test serial");
  //ActuatorSupervisor::switch_pompe(true, 0);
  //navigator.move_to(500.f, 0.f);

  //Serial2.println("Scanner debut");
  //debugTest::scanSerial();
 
}

void loop() {
  /*
 
  //testXbee::update();
    
      if(navTime.check())
    {
        //ActuatorSupervisor::switch_pompe(true, 2);
      navigator.update();
    
    }

		if(controlTime.check()) {
      Odometry::update_reading(&odometry_motor, &odometry_wheel);
      MotorControl::update();
		} 

    
    if(commXBee.check())
    {
      Communication::update();
    }
    if(stateTime.check())
    {   
      MatchDirector::update();      
      fsmSupervisor.update();

    }
 
    if(TestTime.check())
    {
      //asservissementMoteur::update();
    }
  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);
  */
  //lidar code copy-pasted from rplidar examples
  if (IS_OK(rplidar.waitPoint())) {
    float distance = rplidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = rplidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = rplidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = rplidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here...
    //calc nearest int, and round angle accordingly
    float nearest = floorf(angle+0.5);
    if (quality != 0){
      ATC::lidar.set_data((int)nearest, distance, quality);
    }
    

    SerialCtrl.print(angle);
    SerialCtrl.print("\t");
        SerialCtrl.print(distance);      
      SerialCtrl.print("\t");
          SerialCtrl.println(quality); /*
      SerialCtrl.print("\t");
          SerialCtrl.print(startBit);
      SerialCtrl.println("\t");
      */
    
    //rplidar.stop();
    //rplidar.startScan();

    
  } else {

    SerialCtrl.println("err");
    //analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(rplidar.getDeviceInfo(info, 100))) {
       // detected...
       rplidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }

} 
