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

	float pos_x, pos_y, pos_theta, prev_pos_x, prev_pos_y;

	float speed, omega;

	void init(){
		pinMode(MOT_ENCODEUR1_A,INPUT_PULLUP);
		pinMode(MOT_ENCODEUR1_B,INPUT_PULLUP);
		attachInterrupt(MOT_ENCODEUR1_A, isr1, FALLING);
		//attachInterrupt(MOT_ENCODEUR1_A, isr1, RISING);
		_incr1 = 0;

		pinMode(MOT_ENCODEUR1_A,INPUT_PULLUP);
		pinMode(MOT_ENCODEUR1_B,INPUT_PULLUP);
		attachInterrupt(MOT_ENCODEUR1_A, isr1, FALLING);
		//attachInterrupt(MOT_ENCODEUR1_A, isr1, RISING);
		_incr1 = 0;

		pinMode(WHEEL_ENCODEUR1_A,INPUT_PULLUP);
		pinMode(WHEEL_ENCODEUR2_B,INPUT_PULLUP);
		attachInterrupt(WHEEL_ENCODEUR2_A, isr3, RISING);
		//attachInterrupt(MOT_ENCODEUR2_A, isr3, FALLING);
		_incr3 = 0;

		pinMode(WHEEL_ENCODEUR2_A,INPUT_PULLUP);
		pinMode(WHEEL_ENCODEUR2_B,INPUT_PULLUP);
		attachInterrupt(WHEEL_ENCODEUR2_A, isr4, RISING);
		//attachInterrupt(MOT_ENCODEUR2_A, isr4, FALLING);
		_incr4 = 0;

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

	void isr3() {
		if(digitalRead(WHEEL_ENCODEUR1_B)) {
			_incr3++;
			//_incr1--;
		}
		else {
			_incr3--;
			//_incr1++;
		}
	}

	void isr4() {
		if(digitalRead(WHEEL_ENCODEUR2_B)) {
			_incr4++;
			//_incr2--;
		}
		else {
			_incr4--;
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
		//TODO : vérifier formule
		/*Serial.print(" update() >> postheta="); */
		/*Serial.print(pos_theta);
		Serial.print(" angle=");
		Serial.print(angle);*/
		
		prev_pos_x = pos_x;
		prev_pos_y = pos_y;
		pos_x = pos_x + length*cos(pos_theta + angle/2.0); //interpolation entre les deux theta
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;

		Serial.print(" pos_x=");
		Serial.print(pos_x);
		Serial.print(" pos_y=");
		Serial.print(pos_y);
		Serial.print(" new pos_theta=");
		Serial.print(pos_theta);
		Serial.println(".");
		speed = length / CONTROL_PERIOD;
		omega = angle / CONTROL_PERIOD;

		/*
		Serial.print(pos_x);
		Serial.print("\t y:");
		Serial.print(pos_y);
		Serial.print("\t theta: ");
		Serial.print(pos_theta);
		Serial.print("\t V: ");
		Serial.print(speed);
		
		Serial.print("mm/s \t V1:");
		Serial.print(((float)(incr1)*INCR_TO_TOURS/CONTROL_PERIOD));
		Serial.print("tr/s \t V2:");
		Serial.print(((float)(incr2)*INCR_TO_TOURS/CONTROL_PERIOD));
		Serial.print("tr/s \t Omega:");
		*/
		//Serial.print((float)incr1/CONTROL_PERIOD);

		//Serial.println(omega);
	}
}






