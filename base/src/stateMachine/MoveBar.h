/*
 * deploy_front_servo.h
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */
#pragma once

#include <Arduino.h>
#include "AbstractState.h"


class MoveBar : public AbstractState {
public:
	MoveBar(bool isDeployed);

	void enter();
	void doIt();
	void leave();

protected:
	unsigned long time_start;
	bool isDeploying; //false => retracting
	
};
