/*
 * Odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "odometry.h"
#include "params.h"
#include "Arduino.h"
#include "motorControl.h"


Odometry odometry_wheel = Odometry(WHEEL_ENCODEUR1_A,WHEEL_ENCODEUR1_B, WHEEL_ENCODEUR2_A,WHEEL_ENCODEUR2_B, 
	CODER_INCR_TO_MM_1, CODER_INCR_TO_MM_2, CODER_WHEEL_BASE, false);
Odometry odometry_motor = Odometry(MOT_ENCODEUR1_A,MOT_ENCODEUR1_B, MOT_ENCODEUR2_A,MOT_ENCODEUR2_B, 
	INCR_TO_MM_1, INCR_TO_MM_2, WHEELBASE, true);

/*
Odometry odometry_wheel = Odometry(MOT_ENCODEUR1_A,MOT_ENCODEUR1_B, MOT_ENCODEUR2_A,MOT_ENCODEUR2_B, 
	INCR_TO_MM_1, INCR_TO_MM_2, WHEELBASE, true); 
Odometry odometry_motor = Odometry(WHEEL_ENCODEUR1_A,WHEEL_ENCODEUR1_B, WHEEL_ENCODEUR2_A,WHEEL_ENCODEUR2_B, 
	CODER_INCR_TO_MM_1, CODER_INCR_TO_MM_2, CODER_WHEEL_BASE, false);
*/
volatile int Odometry::_incr1 = 0;
volatile int Odometry::_incr2 = 0;
volatile int Odometry::_incr3 = 0;
volatile int Odometry::_incr4 = 0;

Odometry::Odometry(int PIN_COD1_A, int PIN_COD1_B,int PIN_COD2_A,int PIN_COD2_B, 
	const float INCR_TO_MM_1, const float INCR_TO_MM_2, const float WHEEL_BASE,
	bool isMotor) :
	PIN_COD1_A(PIN_COD1_A),
	PIN_COD1_B(PIN_COD1_B),
	PIN_COD2_A(PIN_COD2_A),
	PIN_COD2_B(PIN_COD2_B),
	INCR_TO_MM_1(INCR_TO_MM_1),
	INCR_TO_MM_2(INCR_TO_MM_2),
	WHEEL_BASE(WHEEL_BASE),
	isMotor(isMotor)
{
	nbr1 = 0;
	nbr2 = 0;
}	

Odometry::~Odometry() {
    
}

void Odometry::init() {
		pinMode(PIN_COD1_A,INPUT_PULLUP);
		pinMode(PIN_COD1_B,INPUT_PULLUP); 
		attachInterrupt(PIN_COD1_A, (isMotor) ? isr1 : isr3, FALLING);
		//attachInterrupt(PIN_COD1_A, (isMotor) ? isr1 : isr3, RISING);
		
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
		//SerialCtrl.println("incr3++");
		_incr3++;
		//_incr3--;
	}
	else {
		//SerialCtrl.println("incr3--");
		_incr3--;
		//_incr3++;
	}
}

void Odometry::isr4() {
	if(digitalRead(WHEEL_ENCODEUR2_B)) {
		//SerialCtrl.println("incr4++");
		_incr4++;
		//_incr4--;
	}
	else {
		//SerialCtrl.println("incr4--");
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
		pos_theta = theta;
	}
	

void Odometry::update_reading(Odometry *odom1, Odometry *odom2) {
		cli();
		int incr1 =_incr1;
		int incr2 =_incr2;
		int incr3 =_incr3;
		int incr4 =_incr4;
		_incr1 = _incr2 = _incr3 = _incr4 = 0;
		sei();
		if(odom1 != NULL &&(incr1 != 0 || incr2 != 0))
		{
			(*odom1).update_pos(incr1, incr2);
		}
		if(odom2 != NULL && (incr3 != 0 || incr4 != 0))
		{
			(*odom2).update_pos(incr3, incr4);
		}
		#ifdef DEBUG_ODOMETRY
			SerialCtrl.print((*odom1).get_pos_x());
			SerialCtrl.print("\t");
			SerialCtrl.print((*odom1).get_pos_y());
			SerialCtrl.print("\t");
			SerialCtrl.print((*odom2).get_pos_x());
			SerialCtrl.print("\t");
			SerialCtrl.println((*odom2).get_pos_y());
		#endif


}

void Odometry::update_pos(int incr1, int incr2)
{
		nbr1 += incr1;
		nbr2 += incr2;

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
		/*
		if(WHEEL_BASE == 222.)
		{
			SerialCtrl.println(length);
			SerialCtrl.println(angle);
			SerialCtrl.print(incr2);
			SerialCtrl.print("\t");
			SerialCtrl.print(INCR_TO_MM_1);
			SerialCtrl.print("\t");
			SerialCtrl.print(INCR_TO_MM_2);
			SerialCtrl.print("\t");
			SerialCtrl.print(WHEEL_BASE);
			SerialCtrl.println("\t");
		}
*/
		
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



