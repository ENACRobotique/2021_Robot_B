/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */
#include "Arduino.h"
#include "etat_vide_with_serial.h"
#include "../params.h"
#include "FsmSupervisor.h"

Etat_vide_with_serial etat_vide_with_serial = Etat_vide_with_serial();


Etat_vide_with_serial::Etat_vide_with_serial(String msgBeg = "", String msgUpdate = "", String msgEnd = "") {
	time_start = 0;
	this->msgBeg = msgBeg;
	this->msgUpdate = msgUpdate;
	this->msgEnd = msgEnd;
}

Etat_vide_with_serial::~Etat_vide_with_serial() {
	// TODO Auto-generated destructor stub
}

void Etat_vide_with_serial::enter() {
	SerialCtrl.println(msgBeg);
	SerialDebug.println(msgBeg);
}

void Etat_vide_with_serial::leave() {
	SerialCtrl.println(msgEnd);
	SerialDebug.println(msgEnd);
}

void Etat_vide_with_serial::doIt() {
	SerialCtrl.println(msgUpdate);
	SerialDebug.println(msgUpdate);
	fsmSupervisor.setNextState(NULL);
	SerialCtrl.print("state");
	SerialCtrl.println(fsmSupervisor.is_no_state_set());
}


void Etat_vide_with_serial::reEnter(unsigned long interruptTime){
}

void Etat_vide_with_serial::forceLeave(){
}

void Etat_vide_with_serial::pauseNextState(){
}