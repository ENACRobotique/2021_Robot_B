/*
 * deploy_front_servo.h
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */

#ifndef STATEMACHINE_RetractFrontServo_H_
#define STATEMACHINE_RetractFrontServo_H_
#include <Arduino.h>
#include "AbstractState.h"


class RetractFrontServo : public AbstractState {
public:
	RetractFrontServo();

	void enter();
	void doIt();
	void leave();
	void reEnter(unsigned long InterruptTime);
	void forceLeave();
	void pauseNextState();

protected:
	unsigned long time_start;
};
extern RetractFrontServo retractFrontServo;

#endif /* STATEMACHINE_RetractFrontServo_H_ */