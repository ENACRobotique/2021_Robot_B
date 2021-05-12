/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

//#include "params.h"
#include "ReleaseFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "actuatorSupervisor.h"
#include "etat_begin.h"


ReleaseFrontServo releaseFrontServo = ReleaseFrontServo();


ReleaseFrontServo::ReleaseFrontServo() {
	time_start = 0;
}


void ReleaseFrontServo::enter() {
	time_start = millis();
	ActuatorSupervisor::FrontReleaseVann();

}

void ReleaseFrontServo::leave() {
	SerialDebug.println("Leaving ReleaseFrontServo");
}

void ReleaseFrontServo::doIt() {
	
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		fsmSupervisor.setNextState(&etat_begin);
		
	} 
}


void ReleaseFrontServo::reEnter(unsigned long interruptTime){
}

void ReleaseFrontServo::forceLeave(){
}

void ReleaseFrontServo::pauseNextState(){
}