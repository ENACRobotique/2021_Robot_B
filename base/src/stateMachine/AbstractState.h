/*
 * AbstractState.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_ABSTRACTSTATE_H_
#define STATEMACHINE_ABSTRACTSTATE_H_

#include "arduino.h"

class AbstractState {
public:
	AbstractState();
	virtual ~AbstractState() {};

	virtual void enter() = 0;
	virtual void doIt() = 0;
	virtual void leave() = 0;
	virtual void reEnter(unsigned long InterruptTime) = 0;
	virtual void forceLeave() = 0;
	virtual void pauseNextState() =0;

	unsigned long getFlags() const {
		return flags;
	}

	void setFlags(unsigned long flags) {
		this->flags = flags;
	}
	String name = String();


protected:
	unsigned long flags;
	//unsigned long time_start;
};

#endif /* STATEMACHINE_ABSTRACTSTATE_H_ */