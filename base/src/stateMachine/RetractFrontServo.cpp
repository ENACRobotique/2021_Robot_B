/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "params.h"
#include "RetractFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "actuatorSupervisor.h"
#include "etat_begin.h"


RetractFrontServo retractFrontServo = RetractFrontServo();


RetractFrontServo::RetractFrontServo() {
	time_start = 0;
}


void RetractFrontServo::enter() {
	time_start = millis();
	ActuatorSupervisor::FrontRetractServo();

}

void RetractFrontServo::leave() {
	SerialDebug.println("Leaving RetractFrontServo");
}

void RetractFrontServo::doIt() {
	
	if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
		fsmSupervisor.setNextState(&etat_begin);
		
	} 
}


void RetractFrontServo::reEnter(unsigned long interruptTime){
}

void RetractFrontServo::forceLeave(){
}

void RetractFrontServo::pauseNextState(){
}