/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#pragma once

#include "../ai/Action.h"
#include "AbstractState.h"

class SwitchSection : public AbstractState {
public:
	SwitchSection(Action* action);
	virtual ~SwitchSection();

	void doIt();
	void leave();
	void enter();



private:
	Action* action;

};


