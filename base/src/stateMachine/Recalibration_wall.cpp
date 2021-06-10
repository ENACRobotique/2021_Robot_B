/*
 * MatchDirector.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#include "../FsmSupervisor.h"
#include "Recalibration_wall.h"
#include "navigator.h"
#include "odometry.h"
#include "math.h"

Recalibration_wall recalibration_wall_left = Recalibration_wall(0.0f, 0.0f, true);
Recalibration_wall recalibration_wall_top = Recalibration_wall(2000.f, 0.f, false);
Recalibration_wall recalibration_wall_bottom = Recalibration_wall(0.0f, 0.0f, false);
Recalibration_wall recalibration_wall_right = Recalibration_wall(3000.0f, 0.0f, true);

Recalibration_wall::Recalibration_wall(float targetPos, float targetTheta, bool isX) { //if isX = false => Y
	time_start = 0;
	this->targetPos = targetPos;
	this->targetTheta = targetTheta;
	this->isX = isX;
	wheel_cod_last_reading = -1; //arbitrary value outside of the terrain
}

Recalibration_wall::~Recalibration_wall() {
	// TODO Auto-generated destructor stub
}

void Recalibration_wall::enter() {
	SerialCtrl.print("recalibrating");
	SerialCtrl.print(targetPos);
	SerialCtrl.print(isX);
	navigator.move(50.0f, 0); //40 mm/s
}

void Recalibration_wall::leave() {

}

void Recalibration_wall::doIt() {

	float cur_reading;
	if(isX)
	{
		cur_reading = odometry_wheel.get_pos_x();
	}
	else
	{
		cur_reading = odometry_wheel.get_pos_y();
	}
	SerialCtrl.print(cur_reading);
	SerialCtrl.print("\t");
	SerialCtrl.println(wheel_cod_last_reading);
	if(fabs(cur_reading-wheel_cod_last_reading) <= 0.01f && wheel_cod_last_reading != -1)
	{
		navigator.forceStop();
		float x = (isX) ? targetPos : odometry_wheel.get_pos_x();
		float y = (!isX) ? targetPos : odometry_wheel.get_pos_y();
		odometry_wheel.set_pos(x,y, targetTheta);
		odometry_motor.set_pos(x,y, targetTheta);
		fsmSupervisor.setNextState(NULL);
	}
	wheel_cod_last_reading = cur_reading;

}


void Recalibration_wall::reEnter(unsigned long interruptTime){
}

void Recalibration_wall::forceLeave(){
}

void Recalibration_wall::pauseNextState(){
}