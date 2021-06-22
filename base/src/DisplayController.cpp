#include "DisplayController.h"
#include "params.h"

DisplayController::DisplayController(){

    segments_black = { 0x0, 0x0, 0x0, 0x0 }; 
};

void DisplayController::init(){
    pinMode (DISPALY_CLK, OUTPUT);
    pinMode (DISPLAY_DATA, OUTPUT);

    DisplayObject = TM1637Display(DISPALY_CLK, DISPLAY_DATA);
    DisplayObject.setBrightness(0x0f);
    DisplayObject.setSegments(segments_black);

}
void DisplayController::setNbDisplayed (int NbToDisplay){
    DisplayObject.showNumberDec(NbToDisplay);
};

int DisplayController::getNbDisplayed(){
    return NbDisplayed;
};

void DisplayController::setBlack(){
    DisplayObject.setSegments(segments_black);
};
