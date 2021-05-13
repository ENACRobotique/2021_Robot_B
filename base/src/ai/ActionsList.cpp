#include "Action.h"
#include "../stateMachine/etat_vide_unit_test.h"
#include "../stateMachine/ServoStateList.h"
#include "../stateMachine/Recalibration_wall.h"
#include "../stateMachine/Wait_front_cup_succ.h"

//TODO : Revoir les coordonnées !
//longueur centre du robot à bras déployé : 105
//+ diamètre bas ecocup => 160cm

const float distCentreEcocup = 160.f;
namespace ActionList
{
    /* Ecocup écueils : Ecart de 75 mm entre chaque ecocup */
    //X = 850
    Action EcocupsTopLeft[10] = {
        {700.f, 1850.f, 90.f, &deployFrontServo, 3.0f}, //Going a little bit before the wall + deploy servo before arrival
        {700.f, 1850.f, 90.f, &recalibration_wall, 0.f},
        {700.f, 1900.f, 90.f, &wait_font_cup_succ, 0.f}, //does automatically retractation
        {700.f, 1850.f, 90.f, &etat_vide_unit_test, 0.f}, //backing off the wall
        /*
        {900.f, 1850.f, 270.f, &deploy_back_servo, 3.0f}, 
        {900.f, 1850.f, 270.f, &recalibration_wall, 0.f},
        {700.f, 1850.f, 270.f, &wait_back_cup_succ, 0.f}, //does automatically retractation
        */
    };
    //Y = 400
    Action EcocupsBottomLeft[10] = {
        {10.f, 400.f, 90.f, &deployFrontServo, 3.0f},
    };

    Action depositLeft[10] = 
    {
        {200.f, 1490.f-distCentreEcocup, 90.f, &deployFrontServo, 2.0f},//Front -> direction vert /haut en premier
        //deploy back servo
        //{200.f, 1490.f-distCentreEcocup, 90.f, &release_front_green, 0.0f},
        //{200.f, 1490.f-distCentreEcocup, 90.f, &wait_front_cup_release, 0.0f},
        //{200.f, 920.f+distCentreEcocup, 90.f, &release_back_red, 0.0f},
        //{200.f, 920.f+distCentreEcocup, 90.f, &wait_back_release, 0.0f},
        //{200.f, 1200.f, 270.f, &etat_vide, 0.0f},
        //{200.f, 1490.f-distCentreEcocup, 90.f, &release_back_green, 2.0f}
        //wait back release
        //on va vers le côté rouge
        //on release le vert du front
        //on rétracte le tout, on se centre
    };
    // X = 2150
    Action EcocupsTopRight[10] = {};
    //Y = 400
    Action EcocupsBottomRight[10] = {};
}
 
