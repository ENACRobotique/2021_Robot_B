#include "display.h"
#include "params.h"

controlDisplay::controlDisplay(){};

controlDisplay::init(){
    pinMode (DISPALY_CLK, OUTPUT);
    pinMode (DISPLAY_DATA, OUTPUT);

    DisplayObject = display(DISPALY_CLK, DISPLAY_DATA);
    DisplayObject.setBrightness(0x0f);
    DisplayObject.setSegments({ 0x0, 0x0, 0x0, 0x0 })
};

controlDisplay::setNbDisplayed (int NbToDisplay){
    DisplayObject.showNumberDec(NbToDisplay);
};

controlDisplay::getNbDisplayed(){
    return NbDisplayed;
};

controlDisplay::setBlack(){
    DisplayObject.setSegments({ 0x0, 0x0, 0x0, 0x0 });
};
