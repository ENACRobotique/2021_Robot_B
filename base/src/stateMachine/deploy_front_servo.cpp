/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "params.h"
#include "DeployFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "actuatorSupervisor.h"
#include "etat_begin.h"


DeployFrontServo deployFrontServo = DeployFrontServo();


DeployFrontServo::DeployFrontServo() {
	time_start = 0;
}


void DeployFrontServo::enter() {
	time_start = millis();
	SerialDebug.println("entrée dans l'état capture éco cup");
	DeployFrontServo();

}

void DeployFrontServo::leave() {
	SerialDebug.println("Leaving CaptureEcocup");
}

void DeployFrontServo::doIt() {
	
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		fsmSupervisor.setNextState(&etat_begin);
		
	} 
}


void DeployFrontServo::reEnter(unsigned long interruptTime){
}

void DeployFrontServo::forceLeave(){
}

void DeployFrontServo::pauseNextState(){
}