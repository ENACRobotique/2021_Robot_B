/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_RECALIBRATION_WALL_H_
#define STATEMACHINE_RECALIBRATION_WALL_H_

#include "AbstractState.h"

class Recalibration_wall : public AbstractState {
public:
	Recalibration_wall();
	virtual ~Recalibration_wall();

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

extern Recalibration_wall recalibration_wall;

#endif 