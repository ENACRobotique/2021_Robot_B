#include "LidarXV11.h"
#include "InterfaceLidar.h"
#include "Arduino.h"
#include "../fake_odometry.h"
#include "params.h"
#include <math.h>

InterfaceLidar interface = InterfaceLidar();

InterfaceLidar::InterfaceLidar(){

}

InterfaceLidar::~InterfaceLidar(){
    
}

void InterfaceLidar::init(){
    lidar = LidarXV11();
    for (int i=0; i<6; i++){ // set tout tableau à zéro
        emplacementObstacles[i][0] = 0;
        emplacementObstacles[i][1] = 0;
    }
}

void InterfaceLidar::update_and_calc(uint8_t byte){
    lidar.update(byte); //maj distances ang lidar
    int* all_distances = lidar.get_all_distances(); //get dist ang from lidar
    //see if some dists <= from terrain border
    int x = Odometry::get_pos_x();
    int y = Odometry::get_pos_y();
    int robotAngle = Odometry::get_pos_theta();
    for (int i=0; i<360; i++){
        //ignore obstacles on robot (dist < robot_perimeter/2pi) using params.h
        if (all_distances[i] < ROBOT_PERIMETER/(2*PI)){ // TODO: vérifier unités
            all_distances[i] = -1; //-1 veut dire ignoré
        }
        // calc expected distance to border following angle
        float expected_dist;
        int lid_angle = i - LIDAR_OFFSET_ANGLE - robotAngle;
        //if (atan() <= lid_angle <= )
    }
    // get centers from zones of short distances
    

    //store centers in table 
    //done

    // dans un premier temps, faire en coordonnées relatives
}

int* InterfaceLidar::obstacles(){
    return *emplacementObstacles;
}
