#include "LidarData.h"

LidarData::LidarData(){
    for(int i=0;i<360;i++){
        distance[i] = 0;
        quality[i] = 0;
    }
}

void LidarData::set_data(int angle, float dist, byte qual){
    distance[angle] = dist;
    quality[angle] = qual;
}

float LidarData::get_distance(int angle){
    return distance[angle]; /* place holder du turfu*/
}

byte LidarData::get_quality(int angle){
    return quality[angle];
}