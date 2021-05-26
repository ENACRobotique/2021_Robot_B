/*
 * odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "fake_odometry.h"
#include "params.h"

namespace Odometry{

	volatile int _incr1;
	volatile int _incr2;
	volatile int _incr3;
	volatile int _incr4;
	int nbr1 = 0;
	int nbr2 = 0;
	int nbr3 = 0;
	int nbr4 = 0;

	float pos_x, pos_y, pos_theta;

	float speed, omega;

	void init(){
		_incr1 = 0;
		_incr2 = 0;
		pos_x = 0;
		pos_y = 0;
		pos_theta = 90;
		speed = omega = 0;

	}

	void isr1() {
		
	}

	void isr2() {
		
	}

	float get_pos_x(){
		return pos_x;
	}

	float get_pos_y(){
		return pos_y;
	}

	float get_pos_theta(){
		return normalizeAngle(pos_theta);
	}


	float normalizeAngle(float angle)
	{
	    float newAngle = angle;
	    while (newAngle <= -PI) newAngle += TWO_PI;
	    while (newAngle > PI) newAngle -= TWO_PI;
	    return newAngle;
	}

	float get_speed(){
		return speed;
	}

	float get_omega(){
		return omega;
	}

	void set_pos(float x, float y, float theta){
		pos_x = x;
		pos_y = y;
		pos_theta = PI*theta/180;
	}

	void update() {

	}
}






