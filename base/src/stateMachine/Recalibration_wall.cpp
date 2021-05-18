/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "../FsmSupervisor.h"
#include "Recalibration_wall.h"
#include "navigator.h"
#include "odometry.h"
#include "math.h"


Recalibration_wall::Recalibration_wall(float targetPos, float targetTheta, bool isX) { //if isX = false => Y
	time_start = 0;
	this->targetPos = targetPos;
	this->targetTheta = targetTheta;
	this->isX = isX;
	motor_cod_last_reading = -1; //arbitrary value outside of the terrain
	navigator.move(1.0f, 0); //1 mm/s
}

Recalibration_wall::~Recalibration_wall() {
	// TODO Auto-generated destructor stub
}

void Recalibration_wall::enter() {
}

void Recalibration_wall::leave() {

}

void Recalibration_wall::doIt() {
	if(true) //TODO : timer délai d'intervalle minimum
	{

		float cur_reading;
		if(isX)
		{
			cur_reading = 	Odometry::get_motor_x();
		}
		else
		{
			cur_reading = Odometry::get_motor_y();
		}
		if(fabs(cur_reading-motor_cod_last_reading) <= 0.001f && motor_cod_last_reading != -1)
		{
			navigator.forceStop();
			float x = (isX) ? targetPos : Odometry::get_motor_x();
			float y = (!isX) ? targetPos : Odometry::get_motor_y();
			Odometry::set_pos(x,y, targetTheta);
			fsmSupervisor.setNextState(NULL);
		}
		motor_cod_last_reading = cur_reading;
	}


	


}


void Recalibration_wall::reEnter(unsigned long interruptTime){
}

void Recalibration_wall::forceLeave(){
}

void Recalibration_wall::pauseNextState(){
}