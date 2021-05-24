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

int* InterfaceLidar::get_truexs(){
    return true_x;
}

int* InterfaceLidar::get_trueys(){
    return true_y;
}

int* InterfaceLidar::get_trueang(){
    return true_ang;
}

bool* InterfaceLidar::get_valids(){
    for (int i=0; i<360; i++){
        valids[i] = lidar.is_valid(i);
    }
    return valids;
}

bool* InterfaceLidar::get_inzones(){
    return inzones;
}

int InterfaceLidar::update_and_calc(uint8_t byte){
    int turn = lidar.update(byte); //maj distances ang lidar
    return 0;
    if(turn) {
        Serial2.println("-------------");
        for(int i=0; i<360; i++) {
            //Serial2.printf("%d: %d\n", i, lidar.get_distance(i));
        }
    }
    //if timer is more than 1/10th of second
    if (last_update == -1){
        last_update = millis();
    }
    if (millis()-last_update >= 100 && turn){
        last_update = millis();
        //get dist ang from lidar (shitty workaround copy)
        int x = Odometry::get_pos_x();
        int y = Odometry::get_pos_y();
        int robotAngle = Odometry::get_pos_theta();
        for (int i=0; i<360; i++){
            
            int real_angle = (i + robotAngle)%360;
            
            //Serial.print(i);
            //Serial.print(" ");
            //Serial.print(real_angle);
            int dist = lidar.get_distance(real_angle);
            true_ang[i] = real_angle;
            int true_x_loc = x + (int)(dist * cos(real_angle*DEG_TO_RAD));
            //Serial.print(" ");
            //Serial.print(true_x_loc);
            int true_y_loc = y + (int)(dist * sin(real_angle*DEG_TO_RAD));
            //Serial2.printf("%d: %d  %d, %d\n", real_angle, dist, true_x_loc, true_y_loc);
            //Serial.print(" ");
            //Serial.println(true_y_loc);
            true_x[i] = true_x_loc;
            true_y[i] = true_y_loc;
            inzones[i] = (0 < true_x_loc and true_x_loc < 3000 and 0 < true_y_loc and true_y_loc < 2000) and lidar.is_valid(i);

        }
        // get centers from zones of short distances


        //store centers in table 
        //done
    }
    // dans un premier temps, faire en coordonnées relatives
    return turn;
}

int* InterfaceLidar::obstacles(){
    return *emplacementObstacles;
}
