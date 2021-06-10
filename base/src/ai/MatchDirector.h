/*
 * MatchDirector.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#include "Action.h"

#ifndef MATCH_DIRECTOR_H
#define MATCH_DIRECTOR_H
namespace MatchDirector
{
    void init();
    void update();
    void abs_coords_to(float x, float y); //move to somewhere using abs
    float get_abs_x();
    float get_abs_y();
    float timeToReachCoords();
    void set_current_action(Action *action);

    extern Action *curSection;
    extern bool isStartingLeft;
    extern bool isDrivingBackward; //if move with navigator with positive number, robot goes backward

} // namespace MatchDirector

#endif