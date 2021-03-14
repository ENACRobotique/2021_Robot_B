#include <Arduino.h>
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
Metro TestTime = Metro(1000);
Metro commXBee = Metro((unsigned long)(COMMUNICATION_PERIOD * 1000));
Metro stateTime = Metro((unsigned long)(STATE_PERIOD * 1000));


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  controlTime.reset();
	debugLed.reset();
	navTime.reset();
	TestTime.reset();
	Odometry::init();
	MotorControl::init();

  while (!Serial);
  
}
int i;
int mot1=100;//entre -255 et 255
int mot2=-100;
void loop() {
  MotorControl::testmoteur(mot1,mot2);
		if(controlTime.check()) {
			Serial.print(i);
			Serial.print("\t");
			Odometry::update();
      Navigator::update();
			Serial.print("\t");
			Serial.println(mot2);
			i++;
      Serial.print(" pos x : ");
      Serial.print(Odometry::get_pos_x());
      Serial.print(" pos y : ");
      Serial.print(Odometry::get_pos_y());
		}
		if (TestTime.check())
    {
		  mot2=(mot2+20)%255;
    }

  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);

  //echo back received bytes, just as a test
  while(Serial.available()) {
    Serial.write(Serial.read());
  }

}
