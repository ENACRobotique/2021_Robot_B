/*
 * motorControl.cpp
 *
 *  Created on: 20 mars 2018
 *      Author: elie
 */


#include "odometry.h"
#include "Arduino.h"
#include "params.h"
#include "motorControl.h"
#include "utils.h"

// int clamp(int inf, int sup, float x) {
// 	return min(sup, max(inf, x));
// }

int direction_sign(int nb) {
	if(nb>0) {
		return 0;
	}
	else {
		return 1;
	}
}

namespace MotorControl {

	float cons_speed=0;
	float cons_omega=0;
	
	float Ki_speed = 0.15; //0.2
	float Kp_speed = 0.4; //0.5
	float Kd_speed = 0.05; //0.2
	float Ki_omega = 10;//15;
	float Kp_omega = 40;//10;
	float Kd_omega = 10;//10;

/*
	float Ki_speed = 0.2;//0.2;
	float Kp_speed = 0.5;//0.5;
	float Kd_speed = 0;
	float Ki_omega = 10;//15  20;
	float Kp_omega = 10;//75  30;
	float Kd_omega = 0;
	*/
	float error_integrale_speed=0.01;
	float error_integrale_omega=0;

	float delta_speed=0;
	float delta_omega=0;
	float prev_speed_error=0;
	float prev_omega_error=0;

	void set_cons(float speed, float omega) {
		cons_speed = speed;
		cons_omega = omega;
	}

	float get_cons_speed(){
		return cons_speed;
	}

	float get_cons_omega(){
		return cons_omega;
	}

	void init() {
		pinMode(MOT1_DIR, OUTPUT);
		pinMode(MOT1_PWM, OUTPUT);
		pinMode(MOT2_DIR, OUTPUT);
		pinMode(MOT2_PWM, OUTPUT);
		cons_omega = cons_speed = 0;
		error_integrale_omega = error_integrale_speed = 0;
		prev_omega_error = prev_speed_error = 0;


	}
	void testmoteur(int cmde1, int cmde2) {
		analogWrite(MOT1_PWM, abs(cmde1));
		digitalWrite(MOT1_DIR, direction_sign(cmde1));
		analogWrite(MOT2_PWM, abs(cmde2));
		digitalWrite(MOT2_DIR, direction_sign(cmde2));
	}

	
	void update() {

		float error_speed = cons_speed - odometry_motor.get_speed();
		error_integrale_speed += error_speed;
		delta_speed = error_speed - prev_speed_error;
		prev_speed_error = error_integrale_speed;
		float cmd_speed = Kp_speed * error_speed + Ki_speed * error_integrale_speed + Kd_speed * delta_speed;

		float error_omega = cons_omega - odometry_motor.get_omega();
		error_integrale_omega += error_omega;
		delta_omega = error_omega - prev_omega_error;
		prev_omega_error = error_omega;
		//error_integrale_omega = clamp(-100,100,error_integrale_omega);
		float cmd_omega = Kp_omega * error_omega + Ki_omega * error_integrale_omega + Kd_omega * delta_omega;

		int cmd_mot1 = clamp(-255.f, 255.f, -cmd_speed - cmd_omega);
		int cmd_mot2 = -clamp(-255.f, 255.f, -cmd_speed + cmd_omega);

		analogWrite(MOT1_PWM, abs(cmd_mot1));
		digitalWrite(MOT1_DIR, direction_sign(cmd_mot1));
		analogWrite(MOT2_PWM, abs(cmd_mot2));
		digitalWrite(MOT2_DIR, direction_sign(cmd_mot2));

	//#ifdef DEBUG_ASSERVISSEMENT 
	//a utiliser avec traceur série 
	
	//SerialDebug.print(cons_speed);
	//SerialDebug.print("\t");
	SerialDebug.print(cons_omega);
	SerialDebug.print("\t");
	//SerialDebug.print(odometry_motor.get_speed());
	//SerialDebug.print("\t");
	SerialDebug.println(odometry_motor.get_omega()); 
	//#endif
/*
	
		SerialDebug.print("cmd mot 2 & 1 : ");
		SerialDebug.print(cmd_mot2);
		SerialDebug.print("\t");
		SerialDebug.print(cmd_mot1);
		SerialDebug.print("\t");
		//SerialDebug.println(); */
	}
}
