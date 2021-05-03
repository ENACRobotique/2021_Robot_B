#include "Action.h"
#include "../base/src/stateMachine/DeployFrontServo.h"
Action EcocupsTopLeft[10] = {
    {10.f, 10.f, 90.f, &deployFrontServo, 3.0f}, //Going a little bit before the wall + deploy servo before arrival
}