/*
 * MatchDirector.h
 *
 *  Created on: 09/06/21
 *      Author: Jonathan Muchler
 */

#include "Action.h"

#ifndef MATCH_DIRECTOR_H
#define MATCH_DIRECTOR_H
/** @defgroup namespace Namespaces */

namespace MatchDirector
{
    /**
     * @brief Gestion à haut niveau
     * @addtogroup namespace
     */
    void init();
    void update();

    void addScore(int add);
    void abs_coords_to(float x, float y); //move to somewhere using abs
    float abs_x_to_local(float x);
    float abs_y_to_local(float y);
    float get_abs_x();
    float get_abs_y();

    /**
     * @brief Fonction qui doit être appelé par match director peu de temps avant la fin, modifie les coordonnées à atteindre à la fin
     * @ingroup namespace
     * @param isGirouetteWhite Gère orientation nord/sud
     */
    void compute_final_point(bool isGirouetteWhite);
    
    float timeToReachCoords();
    void set_current_action(Action *action);


    extern Action *curSection;
    extern bool isStartingLeft;
    extern bool isDrivingBackward; //if move with navigator with positive number, robot goes backward

} // namespace MatchDirector

#endif