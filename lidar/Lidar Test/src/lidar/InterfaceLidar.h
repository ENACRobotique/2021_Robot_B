#include "LidarXV11.h"
#include "Arduino.h"
#ifndef LIDAR_INTERFACE_
#define LIDAR_INTERFACE_

class InterfaceLidar{
    public:
        InterfaceLidar();
        virtual ~InterfaceLidar();
        void init();
        void update_and_calc(uint8_t byte);
        int* obstacles();

    //private:
        LidarXV11 lidar;
        int emplacementObstacles[6][2];

};

#endif // LIDAR_INTERFACE_
