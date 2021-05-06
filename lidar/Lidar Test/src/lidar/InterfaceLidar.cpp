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

bool* InterfaceLidar::get_valids(){
    bool valids[360];
    for (int i=0; i<360; i++){
        valids[i] = lidar.is_valid(i);
    }
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
        //see if some dists <= from terrain border
        int x = Odometry::get_pos_x();
        int y = Odometry::get_pos_y();
        int robotAngle = Odometry::get_pos_theta();
        for (int i=0; i<360; i++){
            if (lidar.is_valid(i)){
                float true_x = x + all_dist_ref[i] * cos(i/180*PI);
                float true_y = y + all_dist_ref[i] * sin(i/180*PI);
                //Serial.print(i);
                //Serial.print(" ");
                //Serial.print(true_x);
                //Serial.print(" ");
                //Serial.println(true_y);
                //vérifier si code appartient à zone
                inzones[i] = (0 < true_x and true_x < 3000 and 0 < true_y and true_y < 2000);
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
