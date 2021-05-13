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

RetractFrontServo RetractFrontServo = RetractFrontServo();
RetractBackServo RetractBackServo = RetractBackServo();
RetractFrontGreen RetractFrontGreen = RetractFrontGreen();
RetractFrontRed RetractFrontRed = RetractFrontRed();
RetractBackGreen RetractBackGreen = RetractBackGreen();
RetractBackRed RetractBackRed = RetractBackRed();

void DeployFrontServo::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, true, true);
}
void DeployBackServo::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, false, true);
}

void DeployFrontGreen::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, true, true);
}

void DeployFrontRed::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, true, true);
}

void DeployBackGreen::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, false, true);
}

void DeployBackRed::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, false, true);
}


void RetractFrontServo::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, true, false);
}
void RetractBackServo::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::NONE, false, false);
}

void RetractFrontGreen::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, true, false);
}

void RetractFrontRed::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, true, false);
}

void RetractBackGreen::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::GREEN, false, false);
}

void RetractBackRed::enter() {
    MoveServo::initiate_mvt(ActuatorSupervisor::CupColor::RED, false, false);
}