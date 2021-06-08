#include "Action.h"
#include "../stateMachine/etat_vide_unit_test.h"
#include "../stateMachine/Recalibration_wall.h"
#include "../stateMachine/Wait_front_cup_succ.h"
#include "../stateMachine/MoveServo.h"

//#ifdef DEBUG_MATCH_DIRECTOR
#include "../stateMachine/etat_vide_with_serial.h"
//#endif

namespace ActionList
{
    int test = 5;
    int *score_counter;

    void set_timer_counter(int* timer)
    {
        score_counter = timer;
    }
    #pragma region ecocups
    //TODO : Revoir les coordonnées !
    //longueur centre du robot à bras déployé : 105
    //+ diamètre bas ecocup => 160cm

    const float distCentreEcocup = 160.f;
    //	MoveServo(CupColor color, bool isFront, bool isDeploying, bool isSucc);
    MoveServo deployFrontServo = MoveServo(CupColor::NONE, true, true, true);
    MoveServo deployBackServo = MoveServo(CupColor::NONE, false, true, true);
    MoveServo deployFrontGreen = MoveServo(CupColor::GREEN, true, true, true);
    MoveServo deployFrontRed  = MoveServo(CupColor::RED, true, true, true);
    MoveServo deployBackGreen = MoveServo(CupColor::GREEN, false, true, true);
    MoveServo deployBackRed   = MoveServo(CupColor::RED, false, true, true);

    //still succ -> taking from the écueil
    MoveServo retractFrontServo = MoveServo(CupColor::NONE, true, false, true);
    MoveServo retractBackServo = MoveServo(CupColor::NONE, false, false, true);
    //end of succ -> deposit on the good zone
    MoveServo retractFrontGreen = MoveServo(CupColor::GREEN, true, false, false); 
    MoveServo retractFrontRed  = MoveServo(CupColor::RED, true, false, false);
    MoveServo retractBackGreen = MoveServo(CupColor::GREEN, false, false, false);
    MoveServo retractBackRed   = MoveServo(CupColor::RED, false, false, false);

    //#ifdef DEBUG_MATCH_DIRECTOR
    Action TestMovement[5] =
    {
        {1000.f, 1500.f, 0.f, &Etat_vide_with_serial("phase 1 test movement initie 1"), 0.0f},
        {1200.f, 2000.f, 90.f, &Etat_vide_with_serial("phase 2 test movement initie 2 "), 0.0f},
        {300.f, 1500.f, 180.f, &Etat_vide_with_serial("phase 3 test movement initie 3 "), 0.0f},
    };
    //#endif

    /* Ecocup écueils : Ecart de 75 mm entre chaque ecocup */
    //X = 850
    Action EcocupsTopLeft[10] = {
        {700.f, 1850.f, 90.f, &deployFrontServo, 3.0f}, //Going a little bit before the wall + deploy servo before arrival
        //{700.f, 1850.f, 90.f, &recalibration_wall, 0.f},
        {700.f, 1900.f, 90.f, &wait_font_cup_succ, 0.f}, 
        {700.f, 1900.f, 90.f, &retractFrontServo, 0.f}, 
        {700.f, 1850.f, 0.f, &etat_vide_unit_test, 0.f}, //backing off the wall$
        //moving to the ecocup at the right side
        {900.f, 1850.f, 270.f, &deployBackServo, 3.f},
        //{900.f, 1850.f, 270.f, &recalibration_wall, 0.f},
        //{900.f, 1900.f, 270.f, &wait_back_cup_succ, 0.f},
        {900.f, 1900.f, 270.f, &retractFrontGreen, 0.f},
        {900.f, 1850.f, 270.f, &etat_vide_unit_test, 0.f}, //backing off the wall

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

    #pragma endregion

}
 