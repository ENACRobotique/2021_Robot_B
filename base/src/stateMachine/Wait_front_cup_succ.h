/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_WAIT_CUP_SUC_H_
#define STATEMACHINE_WAIT_CUP_SUC_H_

#include "AbstractState.h"

class Wait_font_cup_succ : public AbstractState {
public:
	Wait_font_cup_succ();
	virtual ~Wait_font_cup_succ();

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

extern Wait_font_cup_succ wait_font_cup_succ;

#endif 