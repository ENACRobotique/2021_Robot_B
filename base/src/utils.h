#pragma once

#include <Arduino.h>

template<typename T> 
const T & clamp( const T & inf, const T & sup, const T & x ) 
{ 
    return min(sup, max(inf, x));
}
