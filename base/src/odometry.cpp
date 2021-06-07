/*
 * Odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "Odometry.h"
#include "params.h"
#include "Arduino.h"
#include "motorControl.h"


Odometry odometry_motor = Odometry(MOT_ENCODEUR1_A,MOT_ENCODEUR1_B, MOT_ENCODEUR2_A,MOT_ENCODEUR2_B, 
	INCR_TO_MM_1, INCR_TO_MM_2, WHEELBASE, true);
Odometry odometry_wheel = Odometry(WHEEL_ENCODEUR1_A,WHEEL_ENCODEUR1_B, WHEEL_ENCODEUR2_A,WHEEL_ENCODEUR2_B, 
	CODER_INCR_TO_MM_1, CODER_INCR_TO_MM_2, CODER_WHEEL_BASE, false);

volatile int Odometry::_incr1 = 0;
volatile int Odometry::_incr2 = 0;
volatile int Odometry::_incr3 = 0;
volatile int Odometry::_incr4 = 0;

Odometry::Odometry(int PIN_COD1_A, int PIN_COD1_B,int PIN_COD2_A,int PIN_COD2_B, 
	const float INCR_TO_MM_1, const float INCR_TO_MM_2, const float WHEEL_BASE,
	bool isMotor = true) :
	PIN_COD1_A(PIN_COD1_A),
	PIN_COD1_B(PIN_COD1_B),
	PIN_COD2_A(PIN_COD2_A),
	PIN_COD2_B(PIN_COD2_B),
	INCR_TO_MM_1(INCR_TO_MM_1),
	INCR_TO_MM_2(INCR_TO_MM_2),
	WHEEL_BASE(WHEEL_BASE),
	isMotor(isMotor)
{

}	

Odometry::~Odometry() {
    
}

void Odometry::init() {
		pinMode(PIN_COD1_A,INPUT_PULLUP);
		pinMode(PIN_COD1_B,INPUT_PULLUP); 
		attachInterrupt(PIN_COD1_A, (isMotor) ? isr1 : isr3, FALLING);
		//attachInterrupt(PIN_COD1_A, isr1, RISING);
		
		pinMode(PIN_COD2_A,INPUT_PULLUP);
		pinMode(PIN_COD2_B,INPUT_PULLUP);
		attachInterrupt(PIN_COD2_A, (isMotor) ? isr2 : isr4, RISING);
		//attachInterrupt(PIN_COD2_A, isr2, FALLING);

		pos_x = pos_y = pos_theta = speed = omega = 0;

	}

void Odometry::isr1() {
	if(digitalRead(MOT_ENCODEUR1_B)) {
		//SerialCtrl.println("isr1");
		_incr1++;
		//_incr1--;
	}
	else {
		_incr1--;
		//_incr1++;
	}
}

void Odometry::isr2() {
	//SerialCtrl.println("isr2");
	if(digitalRead(MOT_ENCODEUR2_B)) {
		_incr2++;
		//_incr2--;
	}
	else {
		_incr2--;
		//_incr2++;
	}
}

void Odometry::isr3() {
		if(digitalRead(WHEEL_ENCODEUR1_B)) {
		_incr3++;
		//_incr3--;
	}
	else {
		_incr3--;
		//_incr3++;
	}
}

void Odometry::isr4() {
	if(digitalRead(WHEEL_ENCODEUR2_B)) {
		_incr4++;
		//_incr4--;
	}
	else {
		_incr4--;
		//_incr4++;
	}
}

float Odometry::get_pos_x() {
		return pos_x;
	}

float Odometry::get_pos_y() {
		return pos_y;
	}

float Odometry::get_pos_theta() {
		return normalizeAngle(pos_theta);
	}


float Odometry::normalizeAngle(float angle)
{
	float newAngle = angle;
	while (newAngle <= -PI) newAngle += TWO_PI;
	while (newAngle > PI) newAngle -= TWO_PI;
	return newAngle;
}

float Odometry::get_speed() {
		return speed;
	}

float Odometry::get_omega() {
		return omega;
	}

void Odometry::set_pos(float x, float y, float theta) {
		pos_x = x;
		pos_y = y;
		pos_theta = PI*theta/180;
	}
	

void Odometry::update() {
		cli();
		int incr1 = (isMotor) ? _incr1 : _incr3;
		int incr2 = (isMotor) ? _incr2 : _incr4; 
		_incr1 = _incr2 = _incr3 = _incr4 = 0;
		sei();

		//nbr1 += incr1;
		//nbr2 += incr2;

		/*SerialDebug.print("nbr1 ");
		SerialDebug.print(nbr1);
		SerialDebug.print(" nbr2 ");
		SerialDebug.println(nbr2);*/
		float length;
		float angle;
		if (MotorControl::get_cons_speed()>=0) {
			length = ((float)(incr1*INCR_TO_MM_1+incr2*INCR_TO_MM_2)/2.0);
			angle = ((float)(incr2*INCR_TO_MM_2-incr1*INCR_TO_MM_1))/WHEEL_BASE;
		}
		else {
			length = ((float)(incr1*INCR_TO_MM_2+incr2*INCR_TO_MM_1)/2.0);
			angle = ((float)(incr2*INCR_TO_MM_1-incr1*INCR_TO_MM_2))/WHEEL_BASE;
		}
		
		pos_x = pos_x + length*cos(pos_theta + angle/2.0); //interpolation entre les deux theta
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;
		speed = length / CONTROL_PERIOD;
		omega = angle / CONTROL_PERIOD;


		#ifdef DEBUG_ODOMETRY
		SerialDebug.print("x:");
		SerialDebug.print(pos_x);
		SerialDebug.print("\t y:");
		SerialDebug.print(pos_y);
		SerialDebug.print("\t pos_theta:");
		SerialDebug.print(pos_theta);
		SerialDebug.print("\tspeed:");
		SerialDebug.print(speed);
		SerialDebug.print("\treal omega:");
		SerialDebug.println(omega);

		#endif
	}



