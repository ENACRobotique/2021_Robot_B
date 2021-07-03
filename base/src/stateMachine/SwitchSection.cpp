/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */


#include "SwitchSection.h"
#include "../ai/MatchDirector.h"
#include "FsmSupervisor.h"
#include "etat_begin.h"
#include "params.h"


SwitchSection::SwitchSection(Action* action) {
	this->action = action;
}

SwitchSection::~SwitchSection() {
	// TODO Auto-generated destructor stub
}

void SwitchSection::enter() {
}

void SwitchSection::leave() {

}

void SwitchSection::doIt() {
	MatchDirector::set_current_action(action);
	fsmSupervisor.setNextState(&etat_begin);
}

