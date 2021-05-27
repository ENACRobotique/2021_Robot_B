/*
 * odometry.h
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */

#ifndef ODOMETRY_H_
#define ODOMETRY_H_

namespace Odometry {
	void isr1();
	void isr2();
	void isr3();
	void isr4();

	void update();
	void init();

	void set_pos(float x, float y, float theta);


	float get_pos_x();
	float get_pos_y();
	float get_pos_theta();
	float normalizeAngle(float angle);
	float get_speed();
	float get_omega();
	float get_motor_x();
	float get_motor_y();

}



#endif /* ODOMETRY_H_ */
