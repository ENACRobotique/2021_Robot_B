/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "Arduino.h"
#include "DeployFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"

DeployFrontServo deployFrontServo = DeployFrontServo();

ControlServo servo = ControlServo(); 

DeployFrontServo::CaptureEcocup() {
	time_start = 0;
}

CaptureEcocup::~CaptureEcocup() {
	// TODO Auto-generated destructor stub
}

void CaptureEcocup::enter() {
	time_start = millis();
	Serial1.println("entrée dans l'état capture éco cup");
	servo.defInitAngle(10);
	servo.init(SERVO3);
	delay(1000);
	servo.resetPos();
	servo.moveServo(120);

}

void CaptureEcocup::leave() {
	Serial1.println("Leaving CaptureEcocup");
}

void CaptureEcocup::doIt() {
	
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		servo.resetPos();
		fmsSupervisor.setNextState(&etat_test);
		
	}
}


void CaptureEcocup::reEnter(unsigned long interruptTime){
}

void CaptureEcocup::forceLeave(){
}

void CaptureEcocup::pauseNextState(){
}