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
        int* get_buffer_dist();
        int* get_raw_dist();

    //private:
        LidarXV11 lidar;
        int buffer_distances[360];
        int emplacementObstacles[6][2];
        float last_update = 0;

};

#endif // LIDAR_INTERFACE_
