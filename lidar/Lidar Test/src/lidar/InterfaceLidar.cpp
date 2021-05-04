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

void InterfaceLidar::update_and_calc(uint8_t byte){
    lidar.update(byte); //maj distances ang lidar
    //if timer is more than 1/10th of second
    if (last_update = 0){
        last_update = millis();
    }
    if (millis()-last_update >= 100){
        last_update = millis();
        //get dist ang from lidar (shitty workaround copy)
        int *all_dist_ref = lidar.get_all_distances();
        for (int i=0; i<360; i++){
            buffer_distances[i] = all_dist_ref[i];
        }
        //see if some dists <= from terrain border
        int x = Odometry::get_pos_x();
        int y = Odometry::get_pos_y();
        int robotAngle = Odometry::get_pos_theta();
        for (int i=0; i<360; i++){
            //ignore obstacles on robot (dist < robot_perimeter/2pi) using params.h
            if (buffer_distances[i] < ROBOT_PERIMETER/(2*PI)){ // TODO: vérifier unités
                buffer_distances[i] = -1; //-1 veut dire ignoré
            }
            else{
                // calc expected distance to border following angle
                float expected_dist;
                int lid_angle = i - LIDAR_OFFSET_ANGLE - robotAngle;
                if (-atan(y/(3000 - x)) <= lid_angle <= atan((2000 - y)/(3000 - x))){//secteur droit
                    expected_dist = (3000 - x)/cos(lid_angle);
                }
                else if (atan((2000 - y)/(3000 - x) <= lid_angle <= 180 - atan((2000-y)/x))){//secteur haut
                    expected_dist = (2000 - y)/sin(lid_angle);
                }
                else if (180 - atan((2000-y)/x <= lid_angle <= 180 + atan(y/x))){//secteur gauche
                    expected_dist = y/cos(lid_angle-180);
                }
                else if (180 + atan(y/x) <= lid_angle <= -atan(y/(3000 - x))){//secteur bas
                    expected_dist = x/cos(lid_angle-90);
                }
                if (buffer_distances[i] > expected_dist){
                    buffer_distances[i] = -1; //trop loin donc ignoré
                }
            }
        }
        // get centers from zones of short distances
        for (int i=0; i<360; i++){
            if (buffer_distances[i] != -1){//is not ignored

            }
        }

        //store centers in table 
        //done
    }
    // dans un premier temps, faire en coordonnées relatives
}

int* InterfaceLidar::obstacles(){
    return *emplacementObstacles;
}
