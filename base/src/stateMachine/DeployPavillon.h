#pragma once 
#include <Arduino.h>
#include "AbstractState.h"

class DeployPavillon : public AbstractState {
public:
	DeployPavillon();

	void enter();
	void doIt();
	void leave();
protected:
    unsigned long time_start;
};

extern DeployPavillon deployPavillon;