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

using ActuatorSupervisor::CupColor;
//Do not call directly this class !
class MoveServo : public AbstractState {
public:
	MoveServo(CupColor color, bool isFront, bool isDeploying, bool isSucc);

	void enter();
	void doIt();
	void leave();

protected:
	unsigned long time_start;
	bool isFront; // false => back
	bool isDeploying; //false => retracting
	bool isSucc;
	CupColor color;
	
};

#endif /* STATEMACHINE_DEPLOY_SERVO_H_ */