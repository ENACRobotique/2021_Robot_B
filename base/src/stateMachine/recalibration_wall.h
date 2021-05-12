/*
//How to get real x/y ???

*/

/*
#include "params.h"
#include "DeployFrontServo.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "actuatorSupervisor.h"
#include "etat_begin.h"


DeployFrontServo deployFrontServo = DeployFrontServo();

ControlServo servo = ControlServo(); 

DeployFrontServo::DeployFrontServo() {
	time_start = 0;
}


void DeployFrontServo::enter() {
	time_start = millis();
	SerialDebug.println("entrée dans l'état capture éco cup");
	DeployFrontServo();

}

void DeployFrontServo::leave() {
	//stop motors
}

void DeployFrontServo::doIt() {
	
	if(about 100ms ago same position) ){
		//get variable of real x position via navigator recalibrate
        //change it
        stop motor
	} 
    if(motors are stopped)
    {
        leave state
    }
}


void DeployFrontServo::reEnter(unsigned long interruptTime){
}

void DeployFrontServo::forceLeave(){
}

void DeployFrontServo::pauseNextState(){
}
*/