/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "Wait_front_cup_succ.h"
#include "RetractFrontServo.h"
#include "FsmSupervisor.h"

Wait_font_cup_succ wait_font_cup_succ = Wait_font_cup_succ();


Wait_font_cup_succ::Wait_font_cup_succ() {
	time_start = 0;
}

Wait_font_cup_succ::~Wait_font_cup_succ() {
	// TODO Auto-generated destructor stub
}

void Wait_font_cup_succ::enter() {
}

void Wait_font_cup_succ::leave() {
	fsmSupervisor.setNextState(&retractFrontServo);
}

void Wait_font_cup_succ::doIt() {


}


void Wait_font_cup_succ::reEnter(unsigned long interruptTime){
}

void Wait_font_cup_succ::forceLeave(){
}

void Wait_font_cup_succ::pauseNextState(){
}