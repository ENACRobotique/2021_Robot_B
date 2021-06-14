/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#pragma once

#include "AbstractState.h"

class Etat_vide_unit_test : public AbstractState {
public:
	Etat_vide_unit_test();
	virtual ~Etat_vide_unit_test();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	void pauseNextState();
	unsigned long get_time_start(){
		return time_start;
	}

private:

	unsigned long time_start;
};

extern Etat_vide_unit_test etat_vide_unit_test;
