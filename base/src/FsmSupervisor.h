/*
 * FsmSupervisor.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_FsmSupervisor_H_
#define STATEMACHINE_FsmSupervisor_H_

#include "./stateMachine/AbstractState.h"

class FsmSupervisor {
public:
	FsmSupervisor();
	virtual ~FsmSupervisor();
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

extern FsmSupervisor FsmSupervisor;

#endif /* STATEMACHINE_FsmSupervisor_H_ */
