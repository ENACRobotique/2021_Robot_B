

#pragma once

#include <Arduino.h>
#include "MoveServo.h"


class DeployFrontServo : public MoveServo {
	void enter();
};
class DeployBackServo : public MoveServo {
	void enter();
};
class DeployFrontGreen : public MoveServo {
	void enter();
};
class DeployFrontRed : public MoveServo {
	void enter();
};
class DeployBackGreen : public MoveServo {
	void enter();
};
class DeployBackRed : public MoveServo {
	void enter();
};


class RetractFrontServo : public MoveServo {
	void enter();
};
class RetractBackServo : public MoveServo {
	void enter();
};
class RetractFrontGreen : public MoveServo {
	void enter();
};
class RetractFrontRed : public MoveServo {
	void enter();
};
class RetractBackGreen : public MoveServo {
	void enter();
};
class RetractBackRed : public MoveServo {
	void enter();
};
extern DeployFrontServo deployFrontServo;
extern DeployBackServo deployBackServo;
extern DeployFrontGreen deployFrontGreen;
extern DeployFrontRed deployFrontRed;
extern DeployBackGreen deployBackGreen;
extern DeployBackRed deployBackRed;

extern RetractFrontServo RetractFrontServo;
extern RetractBackServo RetractBackServo;
extern RetractFrontGreen RetractFrontGreen;
extern RetractFrontRed RetractFrontRed;
extern RetractBackGreen RetractBackGreen;
extern RetractBackRed RetractBackRed;
