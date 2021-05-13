/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "ServoStateList.h"
#include "../FsmSupervisor.h"
#include "../params.h"
#include "../actuatorSupervisor.h"
#include "etat_begin.h"


DeployFrontServo deployFrontServo = DeployFrontServo();
DeployBackServo deployBackServo = DeployBackServo();
DeployFrontGreen deployFrontGreen = DeployFrontGreen();
DeployFrontRed deployFrontRed = DeployFrontRed();
DeployBackGreen deployBackGreen = DeployBackGreen();
DeployBackRed deployBackRed = DeployBackRed();

void DeployFrontServo::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, true);
}
void DeployBackServo::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, false);
}

void DeployFrontGreen::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, true);
}

void DeployFrontRed::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, true);
}

void DeployBackGreen::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, false);
}

void DeployBackRed::enter() {
    DeployServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, false);
}
