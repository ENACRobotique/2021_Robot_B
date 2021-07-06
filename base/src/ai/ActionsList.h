/*
 * MatchDirector.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#ifndef ACTIONS_LIST_H
#define ACTIONS_LIST_H

#include "Action.h"
#include "../stateMachine/AbstractState.h"
#include "../stateMachine/MoveServo.h"
#include "../stateMachine/MoveBar.h"

namespace ActionList
{
    /**
     * 
     * @brief L'ordre des actions va être définie comme un flag
     * par exemple, si on a 6 actions, et qu'on a le flag 001010, la troisiéme et la cinquiéme action dans l'ordre indiqué ont été accompli
     * Comme ça dans le code suivant, on parcourt le flag, on prend le premier 0, s'il est faisable on l'effectue sinon le deuxiéme zero, etc...
     * 
     */
    typedef enum {
        RecupEcueilNord = 1 << 0,
        Phare           = 1 << 1,
        DeposeEcueilNord= 1 << 2,
        MancheAir       = 1 << 3,
        RecupEcueilSud  = 1 << 4,
        DeposeEcueil    = 1 << 5,
    } SectionOrder;

    inline SectionOrder operator|(SectionOrder a, SectionOrder b)
    {
        return static_cast<SectionOrder>(static_cast<int>(a) | static_cast<int>(b));
    }
    
    #define MINIMUM_FLOAT -3.4028235E+38
    extern Action NullAction;
    /**
    @brief return true if action == NullACtion */
    bool isNull(Action* action);

    Action* section(SectionOrder section_id);
    void set_timer_counter(int timer);

    //MoveBar deployBar;
    //MoveBar retractBar;

    #pragma region partie_gauche
    //côté bleu
    extern Action PhareTopLeft[5];
    extern Action EcocupsTopLeft[10];
    extern Action EcocupsTopRight[10];
    extern Action DeposeTopLeft[5];
    extern Action DeposeBottomLeft[5];
    extern Action MancheAirBottomLeft[10];
    extern Action EcocupsBottomLeft[10];
    //côté jaune
    extern Action PhareTopRight[5];
    //extern Action DeposeTopRight[5];
    //extern Action DeposeBottomRight[5];
    extern Action MancheAirBottomRight[10];
    extern Action EcocupsBottomRight[10];
    //On redepose left ici
    //Puis on go final

    #pragma endregion
    extern Action GetToFinal[2];

    extern Action TestStrategieMvtOnly[5];

    extern MoveServo deployFrontServo;

    extern MoveBar deployBar;
    extern MoveBar retractBar; 
}


#endif
