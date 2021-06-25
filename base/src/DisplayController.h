#ifndef DISPLAYKTRLD
#define DISPLAYKTRLD

#include "../lib/TM1637-master/TM1637Display.h"
#include "Arduino.h"

class DisplayController{
    public:
        DisplayController();
        void init();
        void setBlack();
        void setNbDisplayed(int intToDisplay);
        int getNbDisplayed ();
    private:
        uint8_t segments_black;
        int NbDisplayed;
        TM1637Display DisplayObject;
};
#endif