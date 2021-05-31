/*
 * MoveToButtonPause.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#pragma once

#include "AbstractState.h"

class Etat_vide_with_serial : public AbstractState {
public:
	Etat_vide_with_serial(String msgBeg = "", String msgUpdate = "", String msgEnd = "");
	virtual ~Etat_vide_with_serial();

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
	String msgBeg;
	String msgUpdate;
	String msgEnd;
};

extern Etat_vide_with_serial etat_vide_with_serial;