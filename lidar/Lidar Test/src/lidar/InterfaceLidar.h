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
        int* get_raw_dist();
        bool* get_valids();
        bool* get_inzones();

    //private:
        LidarXV11 lidar;
        int emplacementObstacles[6][2];
        float last_update = -1;
        bool inzones[360];

};

#endif // LIDAR_INTERFACE_
