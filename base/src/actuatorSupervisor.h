/*
 * actuatorSupervisor.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#ifndef ACTUATORSUPERVISOR_H_
#define ACTUATORSUPERVISOR_H_

#include "controlServo.h"
namespace ActuatorSupervisor {

	typedef enum 
	{
		RED,
		GREEN,
		NONE
	} CupColor; 

	extern ControlServo armServos[5];
	extern ControlServo otherServos[2]; //[0] = Pavillon, [1] = tige horizontale

	void init();
	void deploy_pav();
	void retract_pav();
	void deploy_bar();
	void retract_bar();
	
	//bool isFrontAttached/detached
	void switch_pompe(bool isOn, int pompe); //control the mosfet on the secondary card, if isOn = true, switch it on, pompe should be between 0 & 4(POMPE1, [...] POMPE 5)
	void switch_ev(bool isOn, int ev);
	void tcaselect(uint8_t i);
	CupColor get_color(int sensor_nb);

	int servo_nb_to_pin(int servo);
	int ev_nb_to_pin(int ev);
    int pompe_nb_to_pin(int pompe);





};


#endif /* ACTUATORSUPERVISOR_H_ */