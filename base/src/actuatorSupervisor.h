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

	void init();
	//bool isFrontAttached/detached
	void switch_pompe(bool isOn, int pompe);
	void switch_ev(bool isOn, int ev);
	CupColor get_color(int sensor_nb);

	int servo_nb_to_pin(int servo);
	int ev_nb_to_pin(int ev);
    int pompe_nb_to_pin(int pompe);




};


#endif /* ACTUATORSUPERVISOR_H_ */