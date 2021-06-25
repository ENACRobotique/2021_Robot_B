#include "ActionsList.h"
#include "Action.h"
#include "../stateMachine/etat_vide_unit_test.h"
#include "../stateMachine/Recalibration_wall.h"
#include "../stateMachine/Wait_front_cup_succ.h"
#include "../stateMachine/MoveServo.h"
#include "../stateMachine/MoveBar.h"
#include "../stateMachine/etat_begin.h"
#include "../stateMachine/SwitchSection.h"

//#ifdef DEBUG_MATCH_DIRECTOR
#include "../stateMachine/etat_vide_with_serial.h"
//#endif

/**
 * @brief action must have nullAction at the end, because it's an "infinite" length array in order to know in matchdirector when to stop and avoid overflow
 * @ingroup namespace
 */
namespace ActionList
{
    int test = 5;
    int *score_counter;

    Action NullAction = {MINIMUM_FLOAT, MINIMUM_FLOAT, MINIMUM_FLOAT, nullptr, MINIMUM_FLOAT};

    const float sizeHalfWidthRobot = 80.f;
    const float sizeHalfLengthRobot = 210.f;

    void set_timer_counter(int* timer)
    {
        score_counter = timer;
    }

    bool isNull(Action* action)
    {
        if (
            (*action).x == NullAction.x
            && (*action).y == NullAction.y
            && (*action).angle == NullAction.angle
            && (*action).state == NullAction.state
            && (*action).countdownState == NullAction.countdownState
        )
        {
            return true;
        }
        return false;

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

    #pragma endregion

    #pragma region switch_sections

    SwitchSection switchEcocup = SwitchSection(&*EcocupsTopLeft);
    SwitchSection switchPhare = SwitchSection(&*PhareTopLeft);

    #pragma endregion

    
    MoveBar deployBar = MoveBar(true);
    MoveBar retractBar = MoveBar(false);  

    Etat_vide_with_serial etat_test_serial_1 = Etat_vide_with_serial("phase 1 test movement initie 1");
    Etat_vide_with_serial etat_test_serial_2 = Etat_vide_with_serial("phase 2 test movement initie 2");
    Etat_vide_with_serial etat_test_serial_3 = Etat_vide_with_serial("phase 3 test movement initie 3");


    Action* section(SectionOrder section_id)
    {
        switch (section_id)
        {
            case RecupEcueilNord:
                /* code */
                break;
            case Phare:
                /* code */
                break;
            case DeposeEcueilNord:
                /* code */
                break;
            case MancheAir:
                /* code */
                break;
            case RecupEcueilSud:
                /* code */
                break;
            case DeposeEcueil:
                /* code */
                break;
            
            default:
                return NULL;
                break;
            }
    }

    /* Ecocup écueils : Ecart de 75 mm entre chaque ecocup */
    //X = 850
    Action EcocupsTopLeft[10] = {
        //{700.f, 1980.f - sizeHalfLengthRobot, 90.f, &deployFrontServo, 3.0f}, //Going a little bit before the wall + deploy servo before arrival
        {700.f, 1980.f - sizeHalfLengthRobot, 90.f, &recalibration_wall_top, 0.f},
        //{700.f, 2000.f- sizeHalfLengthRobot, 90.f, &wait_font_cup_succ, 0.f}, 
        //{700.f, 2000.f- sizeHalfLengthRobot, 90.f, &retractFrontServo, 0.f},
        {700.f, 1800.f, 90.f, &switchPhare, 0.f}, //backing off the wall$ //TODO : faire un SwitchSection
        NullAction 


    };
    /*
        //moving to the ecocup at the right side
        {900.f, 1850.f, 270.f, &deployBackServo, 3.f},
        //{900.f, 1850.f, 270.f, &recalibration_wall, 0.f},
        //{900.f, 1900.f, 270.f, &wait_back_cup_succ, 0.f},
        {900.f, 1900.f, 270.f, &retractFrontGreen, 0.f},
        {900.f, 1850.f, 270.f, &etat_vide_unit_test, 0.f}, //backing off the wall
        */

     Action EcocupsTopRight[10] = {
        {2000.f, 2000.f-(sizeHalfWidthRobot+100.f), 90.f, &deployFrontServo, 3.0f},
         //Going a little bit before the wall + deploy servo before arrival
    };
        //Y = 400 ??
    Action EcocupsBottomRight[10] = {
        {3000.f-(sizeHalfWidthRobot+100.f),250.f , 270.f, &deployFrontServo, 3.0f},
         //Going a little bit before the wall + deploy servo before arrival
    };
    Action EcocupsBottomLeft[10] = {
        {sizeHalfWidthRobot+100.f,250.f , 180.f, &deployFrontServo, 3.0f},
         //Going a little bit before the wall + deploy servo before arrival
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

    Action MancheAirBottomLeft[4] = {
        {200.f, sizeHalfWidthRobot, 0.f, &deployBar, 1.0f},
        {600.f, sizeHalfWidthRobot, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 70.f, &retractBar, 0.0f}, //on léve la deuxiéme manche à air en tournant, et on rétracte de suite
        NullAction
    };
  Action MancheAirBottomRight[4] = {
        {2800.f, sizeHalfWidthRobot, 180.f, &deployBar, 1.0f},
        {2400.f, sizeHalfWidthRobot, 180.f, &etat_begin, 0.0f},
        {2400.f, 200.f, 250.f, &retractBar, 0.0f}, //on léve la deuxiéme manche à air en tournant, et on rétracte de suite
        NullAction
    };

    //Doit être modifié par Get_To_Final dans match director avec les bonnes coords/angle
    /*
    Action GetToFinal[2] =
    {
        {200.f, 100.f, 0.f, &etat_begin, 0.0f},
    };
    */


   Action PhareTopLeft[4] = {
        {600.f, 2000.f - sizeHalfLengthRobot, 0.f, &deployBar, 0.0f},
        {350.f, 2000.f - sizeHalfLengthRobot, -400.f, &retractBar, 0.0f},
        {350.f, 2000.f - sizeHalfLengthRobot, -400.f, &etat_vide_with_serial, 0.0f},
        NullAction
   };

    //

    Action TestStrategieMvtOnly[5] = 
    {
        {600.f, 1800.f, 180.f, &etat_test_serial_1, 0.0f},
        {400.f, 1800.f, -400.f, &etat_test_serial_2, 0.0f},
        {650.f, 1750.f, 90.f, &recalibration_wall_bottom, 0.0f},
        {650.f, 750.f,-400.f, &etat_test_serial_3, 0.0f},
        NullAction
        /*
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        {600.f, 200.f, 0.f, &etat_begin, 0.0f},
        */
    };

    #pragma endregion

}
 
