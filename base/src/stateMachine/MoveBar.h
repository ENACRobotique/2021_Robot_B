/*
 * MoveBar
 *
 *  Created on: 03 april 2021
 *      Author: robot
 */
#pragma once

#include <Arduino.h>
#include "AbstractState.h"


class MoveBar : public AbstractState {
public:
	MoveBar(bool isDeployed, int score = 0);

	void enter();
	void doIt();
	void leave();

protected:
	unsigned long time_start;
	int score;
	bool isDeploying; //false => retracting
	
};
