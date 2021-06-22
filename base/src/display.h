#ifndef DISPLAYKTRLD
#define DISPLAYKTRLD

#include "../lib/TM1637-master/TM1637Display.h"
#include "Arduino.h"

class controlDisplay{
    public:
    controlDisplay();
    void init ();
    void setBlack ();
    void setNbDisplayed (int intToDisplay);
    int getNbDisplayed ();
    private:
    int NbDisplayed;
    TM1637Display DisplayObject;
};
#endif