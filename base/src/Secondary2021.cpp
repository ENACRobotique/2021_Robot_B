
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
//#include "raspberryParser.h"
#include "examples/servoTest.h"
#include "examples/asservissementMoteur.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro debugLed = Metro(2000);
Metro navTime = Metro((unsigned long)(NAVIGATOR_PERIOD * 1000)); //2000
Metro TestTime = Metro((unsigned long)5000);
Metro commXBee = Metro((unsigned long)(COMMUNICATION_PERIOD * 1000));
Metro stateTime = Metro((unsigned long)(STATE_PERIOD * 1000));

float sp[4] = {0, 3.14f, 0, -3.14f};
int i = 0;


void setup() {
  //Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, OUTPUT);

    SerialCtrl.begin(57600);
    Serial.begin(57600);
    #ifdef DEBUG_ASSERVISSEMENT
      Serial.println("cons_speed cons_omega actual_speed actual_omega");
    #endif
    
    //while(!Serial) {}
    Serial.println("initialization serialDebug");
    Serial.println("timer du match mis à 10s !!");
    SerialCtrl.println("initialization serialCtrl");
  controlTime.reset();
	debugLed.reset();
	navTime.reset();
	TestTime.reset();
	Odometry::init();
	MotorControl::init();
  fsmSupervisor.init();
  ActuatorSupervisor::init();
  MatchDirector::init();

  //while (!Serial);
  
}

void loop() {
  

      if(navTime.check())
    {
      navigator.update();
    }

		if(controlTime.check()) {
			Odometry::update();
      MotorControl::update();
		} 

    
    if(commXBee.check())
    {
      Communication::update();
    }
    if(stateTime.check())
    {         
      fsmSupervisor.update();
      MatchDirector::update();
    }
 
    if(TestTime.check())
    {
      //asservissementMoteur::update();
    }
  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);

  //echo back received bytes, just as a test
  /*while(Serial.available()) {
    Serial.write(Serial.read());
  } */

} 
