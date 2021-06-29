#ifndef LIDAR_DATA
#define LIDAR_DATA
#include "RPLidar.h"

/* À implémenter */
class LidarData{
    public:
        LidarData();
        float get_distance(int angle);
        byte get_quality(int angle);
        void set_data(int angle, float distance, byte quality);
    
    private:
        float distance[360];
        byte quality[360];
};

#endif //LIDAR_DATA