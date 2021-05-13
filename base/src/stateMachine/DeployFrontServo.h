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

};
extern DeployFrontServo deployFrontServo;

#endif /* STATEMACHINE_DEPLOYFRONTSERVO_H_ */