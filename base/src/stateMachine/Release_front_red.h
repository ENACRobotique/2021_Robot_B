/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_RELEASE_FRONT_RED_H_
#define STATEMACHINE_RELEASE_FRONT_RED_H_

#include "AbstractState.h"

class Release_front_red : public AbstractState {
public:
	Release_front_red();
	virtual ~Release_front_red();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	void pauseNextState();
	unsigned long get_time_start(){
		return time_start;
	}

private:

	unsigned long time_start;
};

extern Release_front_red release_front_red;

#endif 