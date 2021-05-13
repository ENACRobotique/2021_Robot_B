

#pragma once

#include <Arduino.h>
#include "DeployServo.h"


class DeployFrontServo : public DeployServo {
	void enter();
};
class DeployBackServo : public DeployServo {
	void enter();
};
class DeployFrontGreen : public DeployServo {
	void enter();
};
class DeployFrontRed : public DeployServo {
	void enter();
};
class DeployBackGreen : public DeployServo {
	void enter();
};
class DeployBackRed : public DeployServo {
	void enter();
};
extern DeployFrontServo deployFrontServo;
extern DeployBackServo deployBackServo;
extern DeployFrontGreen deployFrontGreen;
extern DeployFrontRed deployFrontRed;
extern DeployBackGreen deployBackGreen;
extern DeployBackRed deployBackRed;
