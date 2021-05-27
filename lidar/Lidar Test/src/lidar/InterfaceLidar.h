#include "LidarXV11.h"
#include "Arduino.h"
#ifndef LIDAR_INTERFACE_
#define LIDAR_INTERFACE_

class InterfaceLidar{
    public:
        InterfaceLidar();
        virtual ~InterfaceLidar();
        void init();
        int update_and_calc(uint8_t byte);
        int* obstacles();
        int* get_raw_dist();
        bool* get_valids();
        bool* get_inzones();
        int* get_truexs();
        int* get_trueys();
        int* get_trueang();

    //private:
        LidarXV11 lidar;
        int emplacementObstacles[6][2];
        float last_update = -1;
        bool inzones[360];
        int true_x[360];
        int true_y[360];
        bool valids[360];
        int true_ang[360];
};

#endif // LIDAR_INTERFACE_
