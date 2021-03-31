/*
 * fmsSupervisor.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_fmsSupervisor_H_
#define STATEMACHINE_fmsSupervisor_H_

#include "./stateMachine/AbstractState.h"

class fmsSupervisor {
public:
	fmsSupervisor();
	virtual ~fmsSupervisor();
	void setNextState(AbstractState* state);
	void update();
	void init();
	void print_State();

private:

	AbstractState* nextState;
	AbstractState* currentState;
	AbstractState* previousState;
	unsigned long time_obstacle_left;
};

extern fmsSupervisor fmsSupervisor;

#endif /* STATEMACHINE_FSMSUPERVISOR_H_ */
