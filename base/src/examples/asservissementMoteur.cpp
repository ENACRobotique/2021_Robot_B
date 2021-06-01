#include "asservissementMoteur.h"
#include "../motorControl.h"
#include "../navigator.h"

#include "Metro.h"
#include "../params.h"

float cons_test[5] = {0, 3.f, 0, -3.f, 0};


namespace asservissementMoteur {
    int i = 0;
    void update()
    {
        SerialDebug.println(i);
        i = (i==4) ? 0 : i+1;
            navigator.move(50, cons_test[i]);
            //MotorControl::set_cons(cons_test[i], 0);

    }



}