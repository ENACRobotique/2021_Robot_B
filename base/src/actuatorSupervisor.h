#ifndef ACTUATORSUPERVISOR_H_
#define ACTUATORSUPERVISOR_H_

#include "controlServo.h"
namespace ActuatorSupervisor {

	void init();

	void FrontDeployServo();
	void FrontRetractServo();
	void FrontReleaseVann();
	void FrontShutdownVann();
	//bool isFrontAttached/detached



};


#endif /* ACTUATORSUPERVISOR_H_ */