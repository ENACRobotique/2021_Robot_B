#include "LidarData.h"

LidarData::LidarData(bool fake=true){
    if (fake){
        for(int i=0;i<360;i++){
        distance[i] = 65535;
        quality[i] = 14;
        last_time[i] = 0;
    }
    }
    else{
    for(int i=0;i<360;i++){
        distance[i] = 0;
        quality[i] = 0;
        last_time[i] = 0;
    }
    }
}

void LidarData::set_data(int angle, float dist, byte qual){
    distance[angle] = dist;
    quality[angle] = qual;
    last_time[angle] = 0;
}

float LidarData::get_distance(int angle){
    return distance[angle];
}

float LidarData::get_time(int angle){
    return last_time[angle];
}

byte LidarData::get_quality(int angle){
    return quality[angle];
}