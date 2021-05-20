#include "LidarXV11.h"
#include "InterfaceLidar.h"
#include "Arduino.h"
#include "../fake_odometry.h"
#include "params.h"
#include <math.h>
#include <iterator>

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

int* InterfaceLidar::get_raw_dist(){
    return lidar.get_all_distances();
}

int* InterfaceLidar::get_truexs(){
    return true_x;
}

int* InterfaceLidar::get_trueys(){
    return true_y;
}

bool* InterfaceLidar::get_valids(){
    bool valids[360];
    for (int i=0; i<360; i++){
        valids[i] = lidar.is_valid(i);
    }
    return valids;
}

bool* InterfaceLidar::get_inzones(){
    return inzones;
}

void InterfaceLidar::update_and_calc(uint8_t byte){
    lidar.update(byte); //maj distances ang lidar
    //if timer is more than 1/10th of second
    if (last_update == -1){
        last_update = millis();
    }
    if (millis()-last_update >= 100){
        last_update = millis();
        //get dist ang from lidar (shitty workaround copy)
        int *all_dist_ref = lidar.get_all_distances();
        
        int x = Odometry::get_pos_x();
        int y = Odometry::get_pos_y();
        int robotAngle = Odometry::get_pos_theta();
        for (int i=0; i<360; i++){
            int real_angle = i + robotAngle + LIDAR_OFFSET_ANGLE;
            int true_x_loc = x + (int)(all_dist_ref[i] * cos(real_angle/180*PI));
            int true_y_loc = y + (int)(all_dist_ref[i] * sin(real_angle/180*PI));
            true_x[i] = true_x_loc;
            true_y[i] = true_y_loc;
            if (lidar.is_valid(i)){
                //vérifier si point appartient à zone
                inzones[i] = (0 < true_x_loc and true_x_loc < 3000 and 0 < true_y_loc and true_y_loc < 2000);
            }
            else{
                inzones[i] = false;
            }
            
            
        }
        // get centers from zones of short distances


        //store centers in table 
        //done
    }
    // dans un premier temps, faire en coordonnées relatives
}

int* InterfaceLidar::obstacles(){
    return *emplacementObstacles;
}
