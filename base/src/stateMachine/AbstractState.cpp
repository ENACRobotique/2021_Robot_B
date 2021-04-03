/*
 * AbstractState.cpp
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#include "AbstractState.h"

AbstractState::AbstractState() {
	// TODO Auto-generated constructor stub
	flags = 0;
	name = "";
}

/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "Arduino.h"
#include "CaptureEcocup.h"
#include "../FMSSupervisor.h"
#include "Reajustement.h"
#include "../controlServo.h"
#include "../params.h"
#include "etat_test.h"

CaptureEcocup captureEcocup = CaptureEcocup();

ControlServo servo = ControlServo(); 

CaptureEcocup::CaptureEcocup() {
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