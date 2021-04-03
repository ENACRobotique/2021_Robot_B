/*
 * odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "odometry.h"
#include "Arduino.h"
#include "params.h"
#include "motorControl.h"

namespace Odometry{

	volatile int _incr1;
	volatile int _incr2;
	volatile int _incr3;
	volatile int _incr4;
	int nbr1 = 0;
	int nbr2 = 0;
	int nbr3 = 0;
	int nbr4 = 0;
	int totalincre = 0;

	float pos_x, pos_y, pos_theta;

	float speed, omega;

	void init(){
		pinMode(MOT_ENCODEUR1_A,INPUT_PULLUP);
		pinMode(MOT_ENCODEUR1_B,INPUT_PULLUP);
		attachInterrupt(MOT_ENCODEUR1_A, isr1, FALLING);
		//attachInterrupt(MOT_ENCODEUR1_A, isr1, RISING);
		_incr1 = 0;

		pinMode(MOT_ENCODEUR2_A,INPUT_PULLUP);
		pinMode(MOT_ENCODEUR2_B,INPUT_PULLUP);
		attachInterrupt(MOT_ENCODEUR2_A, isr2, RISING);
		//attachInterrupt(MOT_ENCODEUR2_A, isr2, FALLING);
		_incr2 = 0;

		pos_x = pos_y = pos_theta = speed = omega = 0;

	}

	void isr1() {
		if(digitalRead(MOT_ENCODEUR1_B)) {
			_incr1++;
			//_incr1--;
		}
		else {
			_incr1--;
			//_incr1++;
		}
	}

	void isr2() {
			if(digitalRead(MOT_ENCODEUR2_B)) {
				_incr2++;
				//_incr2--;
			}
			else {
				_incr2--;
				//_incr2++;
			}
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
		cli();
		int incr1 = _incr1;
		int incr2 = _incr2;
		_incr1 = _incr2 = 0;
		sei();

		nbr1 += incr1;
		nbr2 += incr2;

		/*Serial.print("nbr1 ");
		Serial.print(nbr1);
		Serial.print(" nbr2 ");
		Serial.println(nbr2);*/
		float length;
		float angle;
		if (MotorControl::get_cons_speed()>=0) {
			length = ((float)(incr1*INCR_TO_MM_1+incr2*INCR_TO_MM_2)/2.0);
			angle = ((float)(incr2*INCR_TO_MM_2-incr1*INCR_TO_MM_1))/WHEELBASE;
		}
		else {
			length = ((float)(incr1*INCR_TO_MM_2+incr2*INCR_TO_MM_1)/2.0);
			angle = ((float)(incr2*INCR_TO_MM_1-incr1*INCR_TO_MM_2))/WHEELBASE;
		}
		
		pos_x = pos_x + length*cos(pos_theta + angle/2.0); //interpolation entre les deux theta
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;
		speed = length / CONTROL_PERIOD;
		omega = angle / CONTROL_PERIOD;


		#ifdef DEBUG_ODOMETRY
		totalincre += incr2;
		Serial.println(totalincre);
		Serial.print("x:");
		Serial.print(pos_x);
		Serial.print("\t y:");
		Serial.print(pos_y);
		Serial.print("\t pos_theta:");
		Serial.print(pos_theta);
		Serial.print("\tspeed:");
		Serial.print(speed);
		Serial.print("\treal omega:");
		Serial.println(omega);

		#endif
	}
}






