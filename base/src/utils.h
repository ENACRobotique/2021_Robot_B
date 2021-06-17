#pragma once

#include <Arduino.h>
#ifndef UTILS_H
#define UTILS_H




template<typename T> 
const T & clamp( const T & inf, const T & sup, const T & x ) 
{ 
    return min(sup, max(inf, x));
}



    const float LEFT_WALL = 0;
    const float RIGHT_WALL = 3000; //TO CHECK;
    const float TOP_WALL = 1000;
    const float BOTTOM_WALL = 0; //TO CHECK;
/*
    //used for recalibration :
float closest_wall_coordinate(int x, int y) //if return -1 : too far to be close to a wall
{
    if(x<=100) //if distance to wall "calculated" from odometry is inferior to 100 mm
    {
        return LEFT_WALL;
    }
    else if(x>= 2900)
    {
        return RIGHT_WALL;
    }
    else if(y<=100)
    {
        return BOTTOM_WALL;
    }
    else if(y>=1900)
    {
        return TOP_WALL;
    }
    else
    {
        return -1.0f;
    }
    
} */
#endif
