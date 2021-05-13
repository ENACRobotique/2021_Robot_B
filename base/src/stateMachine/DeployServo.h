/*
 * deploy_front_servo.h
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */

#ifndef STATEMACHINE_DEPLOY_SERVO_H_
#define STATEMACHINE_DEPLOY_SERVO_H_
#include <Arduino.h>
#include "AbstractState.h"
#include "../actuatorSupervisor.h"

//Do not call directly this class !
class DeployServo : public AbstractState {
public:

	DeployServo();

	virtual void enter() = 0;
	void doIt();
	void leave();

protected:
	void initiate_mvt(ActuatorSupervisor::CupColor color, bool isFront);
	unsigned long time_start;
	bool isFront;
	ActuatorSupervisor::CupColor color;
	
};

#endif /* STATEMACHINE_DEPLOY_SERVO_H_ */