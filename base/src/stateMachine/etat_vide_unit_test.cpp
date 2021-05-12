/*
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "etat_vide_unit_test.h"
#include "../params.h"

Etat_vide_unit_test etat_vide_unit_test = Etat_vide_unit_test();


Etat_vide_unit_test::Etat_vide_unit_test() {
	time_start = 0;
}

Etat_vide_unit_test::~Etat_vide_unit_test() {
	// TODO Auto-generated destructor stub
}

void Etat_vide_unit_test::enter() {
}

void Etat_vide_unit_test::leave() {

}

void Etat_vide_unit_test::doIt() {


}


void Etat_vide_unit_test::reEnter(unsigned long interruptTime){
}

void Etat_vide_unit_test::forceLeave(){
}

void Etat_vide_unit_test::pauseNextState(){
}