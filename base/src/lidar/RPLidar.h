#include "rplidar.h"
#include "Arduino.h"

unsigned long LIDAR_LASTMSG = millis();

void checkAndRestartLidar(){
    if (millis() - LIDAR_LASTMSG > 500UL){
        SerialCtrl.println("restarting lidar");
        LIDAR_LASTMSG = millis();
        Serial1.write(0xA5); 
        Serial1.write(0x20);
    }
}

void readLidar() {
 uint8_t current;
 static uint8_t n = 0;
 static uint8_t quality;
 static bool start;
 static uint16_t angleq6;
 static uint16_t distanceq2;
 
 float angle;
 float distance;

 while(Serial1.available()) {
    // SerialCtrl.print("size ");
    // SerialCtrl.println(Serial1.available());
  current = Serial1.read();

  switch(n) {

   case 0:
    if((current & 1) != (current >> 1 & 1)) {
     quality = current >> 2;
     start = current & 1;
     n = 1;
    }
   break;

   case 1:
    if(current & 1) {
     angleq6 = current >> 1;
     n = 2;
    } else
     n = 0;
   break;

   case 2:
    angleq6 |= current << 7;
    n = 3;
   break;

   case 3:
    distanceq2 = current;
    n = 4;
   break;

   case 4:
    distanceq2 |= current << 8;
    n = 0;
    if(distanceq2) { // Si la lecture est valide
     angle = float(angleq6) / 64.0;
     distance = float(distanceq2) / 4.0;
     int nearest = (180+int(angle+0.5f))%360;
     LIDAR_LASTMSG = millis();

/*
    SerialCtrl.print(nearest);
    SerialCtrl.print("\t");
    SerialCtrl.print(ATC::lidar.get_distance(nearest));
    SerialCtrl.print("\t");
    SerialCtrl.print(ATC::lidar.get_quality(nearest));
    SerialCtrl.print("\n");
    */
    ATC::lidar.set_data(nearest, distance, quality);


    }
   break;
  }
 }
}