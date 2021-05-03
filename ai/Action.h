#ifndef ACTION_H
#define ACTION_H

#include "../base/src/stateMachine/AbstractState.h"

struct Action
{
    float x;
    float y; //navigator turn automatically to go in straight line towards it
    float angle = 0;
    AbstractState *state;
    float countdownState = 0;//state to execute x time before reaching coords
};

#endif