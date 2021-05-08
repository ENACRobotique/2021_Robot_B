#include "Action.h"

#ifndef MATCH_DIRECTOR_H
#define MATCH_DIRECTOR_H
namespace MatchDirector
{
    void test();
    void init();
    void update();
    //void abs_coords_to(); //move to somewhere using abs
    float get_abs_x();
    float get_abs_y();
    float timeToReachCoords();

    extern Action curSection;
    extern bool isStartingLeft;
    extern bool isDrivingBackward; //if move with navigator with positive number, robot goes backward

} // namespace MatchDirector

#endif