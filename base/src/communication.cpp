#include "communication.h"
#include "Arduino.h"
#include <stdlib.h>
#include "motorControl.h"
#include "navigator.h"
#include "odometry.h"




#define COM_DEBUG

namespace Communication {
    
    Serial *serialCtrl = &Serial5; 
    
    static void parse_data();

    char buffer[50];
    int buff_index=0;
    void update() {
        int a;
        a = Serial5.available();
        
        if (a) {
            
            for (int k=0;k<a;k++) {
                char c=Serial5.read();
                //Serial5.write(c);
                if (c=='\n'){
                   
                   buffer[buff_index]='\0';
      //             Serial5.write(buffer,i);
                   parse_data();
                   //value=atoi(buffer);
                   buff_index=0;

                }
                else if (c=='\r') {}
                else {
                    buffer[buff_index]=c;
                    buff_index++;
                }
            }
        }



    }

    static void parse_data(){
        if(buffer[0] == 's') {
            MotorControl::set_cons(0,0);
            navigator.forceStop();
            #ifdef COM_DEBUG
            Serial5.println("Stopped!");
            #endif
        }
        else if(buffer[0] == 'm') {
            float x,y;
            int nb = sscanf(buffer, "m %f %f", &x, &y);
            if(nb == 2) {
                navigator.move_to(x, y);
                #ifdef COM_DEBUG
                Serial5.print("Moving to ");
                Serial5.print(x);
                Serial5.print("\t");
                Serial5.println(y);
                #endif
            }
        }
        else if(buffer[0] == 'o') {
            Serial5.print("pos: ");
            Serial5.print(Odometry::get_pos_x());
            Serial5.print("\t");
            Serial5.print(Odometry::get_pos_y());
            Serial5.print("\t");
            Serial5.println(Odometry::get_pos_theta());
        } else if(buffer[0] == 't') {
            //in degrees
            float angle;
            int nb = sscanf(buffer, "t %f", &angle);
            if(nb == 1) {
                navigator.turn_to(angle);
            }
        }
        else if(buffer[0] == 'i'){
            raspberryparser.parseData(buffer);
        }
        else if(buffer[0]=='c') {
            fmsSupervisor.setNextState(&reajustement);
        }
        else if(buffer[0]=='e') {
            fmsSupervisor.print_State();
        }

        buff_index = 0;
    }
}       