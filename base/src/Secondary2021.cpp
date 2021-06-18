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
#include "lidar/Lidar.h"
//#include "raspberryParser.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro debugLed = Metro(2000);
Metro navTime = Metro((unsigned long)(NAVIGATOR_PERIOD * 1000)); //2000
Metro TestTime = Metro((unsigned long)5000);
Metro commXBee = Metro((unsigned long)(COMMUNICATION_PERIOD * 1000));
Metro stateTime = Metro((unsigned long)(STATE_PERIOD * 1000));

float sp[4] = {0, 3.14f, 0, -3.14f};
int i = 0;

#include "ai/ActionsList.h"
void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(11, OUTPUT);
  //testXbee::init();
    //SerialCtrl.begin(57600);
    Serial.begin(57600);
    //SerialDebug.begin(57600);
    SerialDebug.println("test SerialDebug 1");
    //SerialCtrl.println(ActionList::isNull(&ActionList::TestStrategieMvtOnly[0]));
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
  /*
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
*/
  debugTest::scanSerial();
  //while (!Serial);
  SerialCtrl.println("test serialctrl");
  Serial.println("test serial");
  //ActuatorSupervisor::switch_pompe(true, 0);
  //navigator.move_to(500.f, 0.f);
  //pwm.begin();

  //Serial2.println("Scanner debut");
  //debugTest::scanSerial();
  
}

void loop() {
    debugTest::scanSerial();
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
      //MatchDirector::update();      
      fsmSupervisor.update();

    }
 
    if(TestTime.check())
    {
      asservissementMoteur::update();
    }
  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);
  
*/
} 
