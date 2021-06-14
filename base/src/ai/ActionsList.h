/*
 * MatchDirector.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#ifndef ACTIONS_LIST_H
#define ACTIONS_LIST_H

#include "Action.h"
#include "../stateMachine/AbstractState.h"
namespace ActionList
{
    void set_timer_counter(int timer);
    extern Action EcocupsTopLeft[10];
    extern Action TestMovement[5];

    extern Action GetToFinal[2];

    extern Action TestStrategieMvtOnly[4];
}


#endif
