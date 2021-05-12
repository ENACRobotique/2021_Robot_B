/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_RELEASE_FRONT_GREEN_H_
#define STATEMACHINE_RELEASE_FRONT_GREEN_H_

#include "AbstractState.h"

class Release_front_green : public AbstractState {
public:
	Release_front_green();

	void doIt();
	void leave();
	void enter();
};

extern Release_front_green release_front_green;

#endif 