/*
 * deploy_front_servo.h
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */

#ifndef STATEMACHINE_RELEASEFRONTSERVO_H_
#define STATEMACHINE_RELEASEFRONTSERVO_H_
#include <Arduino.h>
#include "AbstractState.h"


class ReleaseFrontServo : public AbstractState {
public:
	ReleaseFrontServo();

	void enter();
	void doIt();
	void leave();
	void reEnter(unsigned long InterruptTime);
	void forceLeave();
	void pauseNextState();

protected:
	unsigned long time_start;
};
extern ReleaseFrontServo releaseFrontServo;

#endif /* STATEMACHINE_RELEASEFRONTSERVO_H_ */