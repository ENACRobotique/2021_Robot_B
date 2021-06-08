#include "pathfinding.h"
#include "params.h"
#include <math.h>

Geom_Vec::Geom_Vec(float x, float y){
    this->x = x;
    this->y = y;
}

Geom_Vec::Geom_Vec(float start[2], float end[2]){
    this->x = end[0] - start[0];
    this->y = end[1] - start[1];
}

Geom_Vec Geom_Vec::scale(float factor){
    return Geom_Vec(x*factor, y*factor);
}

float Geom_Vec::length(){
    return sqrtf(x*x + y*y);
}

float Geom_Vec::dot(Geom_Vec other){
    return x*other.x + y*other.y;
}

float Geom_Vec::get_angle(){
    if (x != 0){
        float at = (float) atan(y/x)*360/(2*PI);
        if (x >= 0){ return at; }
        else{ return 180 + at; }
    }
    else{
        if (y>0){ return 90; }
        else if (y < 0){ return -90; }
        else{ return 0; }
    }
}

float Geom_Vec::dist_to_point(float point[2]){
    Geom_Vec vec_point(point[0], point[1]);
    float len_line = this->length();
    Geom_Vec sc_line = this->scale(1/len_line);
    Geom_Vec sc_ptvec = vec_point.scale(1/len_line);
    float t = sc_line.dot(sc_ptvec);
    if (t < 0){
        t = 0;
    }
    else if (t > 1) {
        t = 1;
    }
    Geom_Vec nearest = this->scale(t);
    float nearest_coords[2] = {nearest.x, nearest.y};
    float dist = Geom_Vec(point, nearest_coords).length();
    return dist;
}


