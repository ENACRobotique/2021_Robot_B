#include "MoveBar.h"
#include "etat_begin.h"
#include "../actuatorSupervisor.h"
#include "params.h"
#include "FsmSupervisor.h"
#include "../ai/MatchDirector.h"


MoveBar::MoveBar(bool isDeployed, int score) {
    this->isDeploying = isDeployed;
    this->score = score;
}

void MoveBar::enter() {
    if(isDeploying)
    {
        SerialCtrl.println("deploying bar ! ");
        ActuatorSupervisor::deploy_bar();
    }
    else
    {
        ActuatorSupervisor::retract_bar();
    }
    

}

void MoveBar::doIt() {
    if(((millis() - time_start) > SERVO_MOVEMENT_DURATION*2) ){
        fsmSupervisor.setNextState(&etat_begin);
	} 
}

void MoveBar::leave() {
    MatchDirector::addScore(this->score);
    SerialDebug.println("Leaving Deployment of Servo Pavillon");
}
