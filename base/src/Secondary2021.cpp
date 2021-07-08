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
//#include "lidar/rplidar.h"
#include "lidar/RPLidar.h"
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
bool lidarStarted = false;

float prevX = -1.;
float prevY = -1.;


//LidarData ATC::lidar; because
// Lidar data container is initialised in pathfinding, as part of ATC namespace (not sure if good idea)

#define RPLIDAR_MOTOR 38 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 

float startTime = 0;
#include "ai/ActionsList.h"
void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(24, INPUT_PULLUP); //tirette
  pinMode(COLOR, INPUT_PULLUP); //switch couleur
  //testXbee::init();
  Serial1.begin(115200); //lidar
  Serial2.begin(57600);
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
  for(int i=0; i<10; i++) {
    SerialCtrl.println("starting...");
    delay(10);
  }

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  // start lidar motor
  analogWrite(RPLIDAR_MOTOR, 200);
  // bind the RPLIDAR driver to the arduino hardware serial
  
  // set pin modes

  if(digitalRead(COLOR) == LOW){
    SerialCtrl.println("Color switch in yellow(right) position");
    MatchDirector::isStartingLeft = false;
  }
  else{
    SerialCtrl.println("Color switch in blue(left) position");
  }

  
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

   Serial1.write(0xA5); 
   Serial1.write(0x20);

  //debugTest::scanSerial();
  displayController.init();

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
 
 if(debugLed.check())
 {
    
   /*while(Serial1.available())
   {
     Serial1.flush();
   }*/
 }
  if(millis() -startTime >= 2000.f && lidarStarted == false)
  {
      analogWrite(RPLIDAR_MOTOR, 255);
    SerialCtrl.println("reinit lidar");
    lidarStarted = true;
    Serial1.write(0xA5); 
   Serial1.write(0x20);
  }
    if(digitalRead(TIRETTE) == HIGH && MatchDirector::hasStarted == false)
    {
      if(digitalRead(COLOR) == LOW){
        MatchDirector::set_current_action(ActionList::EcocupsTopRight);
      }
      else{
        MatchDirector::set_current_action(ActionList::EcocupsTopLeft);
      }
      
      MatchDirector::hasStarted = true;

    }
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

      float full_pos[3] = {MatchDirector::get_abs_x(), MatchDirector::get_abs_y(), odometry_wheel.get_pos_theta()};
      bool isFront = (navigator.sgn == 1) ? true : false;
      if(ATC::proximity_check(&ATC::lidar, true, full_pos) && (millis()-MatchDirector::start_millis < MatchDirector::timer*1000))
      {
        SerialCtrl.println("robot stopped due to obstacle in front");
        MatchDirector::isRobotStopped = true;
        prevX = navigator.x_target;
        prevY = navigator.y_target;
        navigator.forceStop();
      }
      else if (MatchDirector::isRobotStopped)
      {
        SerialCtrl.println("robot restarting, obstacle noved ");
        MatchDirector::isRobotStopped = false;
        navigator.move_to(prevX, prevY);
      }
      if((millis() -startTime >= 3000.f && lidarStarted == true)||true){
        //checkAndRestartLidar();
      }
      
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

    //as fast as possible : 
    readLidar();

  //send_odom_report(12.2, 34.2, 14.8);
  //delay(800);



  
} 
