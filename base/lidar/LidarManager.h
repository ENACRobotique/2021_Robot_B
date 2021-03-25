/*
 * LidarManager.cpp
 *
 *  Created on: 14 mai 2019
 *      Author: robot
 */

#include "LidarXV11.h"
#include "Arduino.h"

class LidarManager {
public:
	LidarManager();
	virtual ~LidarManager();
	void init();
	void update();
	bool is_ignored(int lidarAngle);
	bool is_ignored2(int x, int y);
	int xObstacle(int lidarAngle);
	int yObstacle(int lidarAngle);
	bool obstacleDetected(int lidarAngleA, int lidarAngleB);
	LidarXV11 lidar = LidarXV11();

private:
	//LidarXV11 lidar = LidarXV11();
	const int NB_OBSTACLES = 2;
	const int DIST_MIN = 350;

};

