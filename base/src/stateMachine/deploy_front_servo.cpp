/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "params.h"
#include "DeployFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "controlServo.h"


DeployFrontServo deployFrontServo = DeployFrontServo();

ControlServo servo = ControlServo(); 

DeployFrontServo::DeployFrontServo() {
	//time_start = 0;
}


void DeployFrontServo::enter() {
	//time_start = millis();
	SerialDebug.println("entrée dans l'état capture éco cup");
	servo.defInitAngle(10);
	servo.init(SERVO3);
	delay(1000);
	servo.resetPos();
	servo.moveServo(120);

}

void DeployFrontServo::leave() {
	SerialDebug.println("Leaving CaptureEcocup");
}

void DeployFrontServo::doIt() {
	/*
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		servo.resetPos();
		fmsSupervisor.setNextState(&etat_test);
		
	} */
}


void DeployFrontServo::reEnter(unsigned long interruptTime){
}

void DeployFrontServo::forceLeave(){
}

void DeployFrontServo::pauseNextState(){
}