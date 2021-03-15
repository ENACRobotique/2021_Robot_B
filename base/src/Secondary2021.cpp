#include "Arduino.h"
#include "odometry.h"
#include "motorControl.h"
#include "params.h"
#include "Metro.h"
#include "communication.h"
#include "navigator.h"
//#include "raspberryParser.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro debugLed = Metro(2000);
Metro navTime = Metro((unsigned long)(NAVIGATOR_PERIOD * 1000)); //2000
Metro TestTime = Metro(5000);
Metro commXBee = Metro((unsigned long)(COMMUNICATION_PERIOD * 1000));
Metro stateTime = Metro((unsigned long)(STATE_PERIOD * 1000));


void setup() {
  //Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

    Serial5.begin(57600);

  controlTime.reset();
	debugLed.reset();
	navTime.reset();
	TestTime.reset();
	Odometry::init();
	MotorControl::init();

  //while (!Serial);
  
}
int i;
int mot1=50;//entre -255 et 255
int mot2=-50;
void loop() {

      if(navTime.check())
    {
      navigator.update();
    }
  /*
  MotorControl::testmoteur(mot1,mot2); */
		if(controlTime.check()) {

			Odometry::update();
      //MotorControl::update();
    Serial.println("  ");
      Serial.print(" pos x : ");
      Serial.print(Odometry::get_pos_x());
      Serial.print(" pos y : ");
      Serial.print(Odometry::get_pos_y());
		} 

    if(TestTime.check())
    {
      mot1 = 0;
      mot2=0;
    }
    /*
		if (TestTime.check())
    {
		  mot2=(mot2+20)%255;
    }
    */
    if(commXBee.check())
    {
      Communication::update();
    }
 
  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);

  //echo back received bytes, just as a test
  while(Serial.available()) {
    Serial.write(Serial.read());
  }

}
