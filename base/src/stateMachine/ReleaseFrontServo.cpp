/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "params.h"
#include "ReleaseFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "actuatorSupervisor.h"
#include "etat_begin.h"


ReleaseFrontServo releaseFrontServo = ReleaseFrontServo();

ControlServo servo = ControlServo(); 

ReleaseFrontServo::ReleaseFrontServo() {
	time_start = 0;
}


void ReleaseFrontServo::enter() {
	time_start = millis();
	SerialDebug.println("entrée dans l'état capture éco cup");
	ReleaseFrontServo();

}

void ReleaseFrontServo::leave() {
	SerialDebug.println("Leaving CaptureEcocup");
}

void ReleaseFrontServo::doIt() {
	
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		servo.resetPos();
		fsmSupervisor.setNextState(&etat_begin);
		
	} 
}


void ReleaseFrontServo::reEnter(unsigned long interruptTime){
}

void ReleaseFrontServo::forceLeave(){
}

void ReleaseFrontServo::pauseNextState(){
}