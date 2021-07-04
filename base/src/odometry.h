/*
 * odometry.h
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 * 		Modifié par Jonathan Muchler, 2021
 */
#include "params.h"

#ifndef ODOMETRY_H_
#define ODOMETRY_H_

/* Odometry receive data from encoders, and provide methods with calculated estimated x, y, angle from these encoders */
class Odometry
{
	public:
		Odometry(int PIN_COD1_A, int PIN_COD1_B,int PIN_COD2_A,int PIN_COD2_B, 
			const float INCR_TO_MM_1, const float INCR_TO_MM_2, const float WHEEL_BASE, bool isMotor = true);
		~Odometry();

		void set_pos(float x, float y, float theta); //dans un référentiel local du robot (0,0 au départ)
		float normalizeAngle(float angle);

		float get_pos_x();
		float get_pos_y();
		float get_pos_theta();
		float get_speed();
		float get_omega();

		static void update_reading(Odometry *odom1 = NULL, Odometry *odom2 = NULL);
		void update_pos(int incr1, int incr2);
		void init();


		int nbr1;
		int nbr2;
	private:
		const int PIN_COD1_A;
		const int PIN_COD1_B;
		const int PIN_COD2_A;
		const int PIN_COD2_B;
		const float INCR_TO_MM_1;
		const float INCR_TO_MM_2;
		const float WHEEL_BASE;
		bool isMotor; //sert à définir si on utilise isr1/2 ou isr3/4

		static volatile int _incr1;
		static volatile int _incr2;
		static volatile int _incr3;
		static volatile int _incr4;


		float pos_x, pos_y, pos_theta;

		float speed, omega;

		//on peut pas appeler attachInterrupt avec une fonction déclarée dans une instance
		//https://arduino.stackexchange.com/questions/4862/attachinterrupt-in-a-library
		static void isr1(); //fct° déclenché par un signal d'un codeur, qui va voir le sens du déphasage & qui gére l'incrémentation
		static void isr2();
		static void isr3();
		static void isr4();
	
};

extern Odometry odometry_motor;
extern Odometry odometry_wheel;

#endif /* ODOMETRY_H_ */

/*

1419
18:50:27.597 -> 1405

18:51:01.226 -> 1428
18:51:01.226 -> 1454


18:51:39.930 -> 1413
18:51:39.930 -> 1463


*/