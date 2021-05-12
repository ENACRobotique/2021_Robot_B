#include "Action.h"
#include "../stateMachine/etat_vide_unit_test.h"


namespace ActionList
{
    Action EcocupsTopLeft[10] = {
        //{10.f, 10.f, 90.f, &deployFrontServo, 3.0f},
        {10.f, 10.f, 90.f, &etat_vide_unit_test, 3.0f}, //Going a little bit before the wall + deploy servo before arrival
    };
}
 
