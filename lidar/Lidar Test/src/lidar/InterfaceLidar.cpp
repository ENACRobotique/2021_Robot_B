#include "LidarXV11.h"
#include "InterfaceLidar.h"
#include "Arduino.h"
#include "../fake_odometry.h"

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
    //get centers from zones of short distances
    //store centers in table 
    //done
}

int* InterfaceLidar::obstacles(){
    return *emplacementObstacles;
}
