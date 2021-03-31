/*
 * fsmSupervisor.cpp
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#include "fsmSupervisor.h"
#include "Arduino.h"
#include "./stateMachine/AbstractState.h"
#include "./stateMachine/CaptureEcocup.h"
#include "./stateMachine/Reajustement.h"
#include "./stateMachine/etat_test.h"
#include "./stateMachine/etat_begin.h"
#include "kalman.h"

fsmSupervisor fsmSupervisor = fsmSupervisor();

fsmSupervisor::fsmSupervisor() {
	// TODO Auto-generated constructor stub
	nextState = NULL;
	currentState = NULL;
	previousState = NULL;
	time_obstacle_left = 0;
}

fsmSupervisor::~fsmSupervisor() {
	// TODO Auto-generated destructor stub
}

void fsmSupervisor::setNextState(AbstractState* state) {
	nextState = state;
}

void fsmSupervisor::update() {
	/*if (millis() - tiretteState.get_time_start() > TIME_RACE){
		fsmSupervisor.setNextState(&deadState); //TODO Créer un état où le robot s'arrête
	}

	if(currentState == &pauseState && pauseState.isTooLong()){
		previousState->pauseNextState();
	}*/

	if(nextState != NULL && nextState != currentState){
		currentState->leave();
		nextState->enter();
		currentState = nextState;
		nextState = NULL;
	}

	currentState->doIt();

	/*if(currentState->getFlags() & E_ULTRASOUND){
		usManager.update();
		if(usManager.obstacleDetected()){
			time_obstacle_left = 0;
			if(currentState != &pauseState){			// on va dans l'état pause
				currentState->forceLeave();
				previousState = currentState;
				currentState = &pauseState;
				pauseState.enter();
			}

		}
		else {
			if(currentState == &pauseState && previousState != NULL){		// on revient dans l'état précédent !
				if(time_obstacle_left == 0){
					time_obstacle_left = millis();
				}
				if(millis() - time_obstacle_left > DETECTION_STOP_TIME){ //Permet de ne pas repartir directement quand on ne détecte plus d'adversaires
					pauseState.leave();
					previousState->reEnter(pauseState.getPauseTime());
					currentState = previousState;
					previousState = &pauseState;
					time_obstacle_left = 0; //May be useless (just like the primary)
				}
			}
		}
	}*/
}

/*
void fsmSupervisor::init(AbstractState* state) {
	currentState = state;
	state->enter();
}
*/
void fsmSupervisor::init(){
	currentState = &etat_begin;
	currentState->enter();
}

void fsmSupervisor::print_State() {
	Serial1.println("Current state :" + currentState->name);
}
