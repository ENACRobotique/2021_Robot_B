/*
 * deploy_front_servo.h
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */

#ifndef STATEMACHINE_DEPLOYFRONTSERVO_H_
#define STATEMACHINE_DEPLOYFRONTSERVO_H_
#include <Arduino.h>
#include "AbstractState.h"


class DeployFrontServo : public AbstractState {
public:
	DeployFrontServo();

	void enter();
	void doIt();
	void leave();
	void reEnter(unsigned long InterruptTime);
	void forceLeave();
	void pauseNextState();

protected:
	unsigned long time_start;
};
extern DeployFrontServo deployFrontServo;

#endif /* STATEMACHINE_DEPLOYFRONTSERVO_H_ */