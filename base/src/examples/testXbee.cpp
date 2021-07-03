#include "Arduino.h"

namespace testXbee {
    void init()
    {
        //Serial2.begin(57600);
        Serial2.println("testXbee");
    }
    void update()
    {
        Serial2.println("testXbee update ");
        delay(500);
    }
}