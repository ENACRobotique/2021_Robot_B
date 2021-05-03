#include "communication.h"
#include "Arduino.h"
#include <stdlib.h>
#include "motorControl.h"
#include "navigator.h"
#include "odometry.h"
#include "FsmSupervisor.h"
#include "./stateMachine/DeployFrontServo.h"
#include "params.h"


#define COM_DEBUG

namespace Communication {
    
    
    static void parse_data();

    char buffer[50];
    int buff_index=0;
    void update() {
        int a;
        a = SerialCtrl.available();
        #ifdef IHM
            SerialCtrl.print("R 2 "); + 
            SerialCtrl.print(Odometry::get_pos_x());
            SerialCtrl.print(" ");
            SerialCtrl.print(Odometry::get_pos_y());
            SerialCtrl.print(" ");
            SerialCtrl.println(Odometry::get_pos_theta());
            //SerialCtrl.println("");
        #endif
        if (a) {
            for (int k=0;k<a;k++) {
                char c=SerialCtrl.read();
                //serialCtrl.write(c);
                if (c=='\n'){
                   
                   buffer[buff_index]='\0';
      //             serialCtrl.write(buffer,i);
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
        SerialDebug.print(buffer);
        if(buffer[0] == 's') {
            MotorControl::set_cons(0,0);
            navigator.forceStop();
            #ifdef COM_DEBUG
            SerialCtrl.println("Stopped!");
            #endif
        }
        else if(buffer[0] == 'm') {
            float x,y;
            int nb = sscanf(buffer, "m %f %f", &x, &y);
            if(nb == 2) {   
                navigator.move_to(x, y);
                #ifdef COM_DEBUG
                SerialCtrl.print("Moving to ");
                SerialCtrl.print(x);
                SerialCtrl.print("\t");
                SerialCtrl.println(y);
                #endif
            }
        }
        else if(buffer[0] == 'P') {
            float x,y;
            int nb = sscanf(buffer, "P 2 %f %f", &x, &y);
            if(nb == 2) {   
                navigator.move_to(x, y);
                SerialDebug.println(x);
            }
        }
        else if(buffer[0] == 'o') {
            SerialCtrl.print("pos: ");
            SerialCtrl.print(Odometry::get_pos_x());
            SerialCtrl.print("\t");
            SerialCtrl.print(Odometry::get_pos_y());
            SerialCtrl.print("\t");
            SerialCtrl.println(Odometry::get_pos_theta());
        } else if(buffer[0] == 't') {
            //in degrees
            float angle;
            int nb = sscanf(buffer, "t %f", &angle);
            if(nb == 1) {
                navigator.turn_to(angle);
            }
        }
        else if(buffer[0] == 'd') {
            fsmSupervisor.setNextState(&deployFrontServo);
        }


        buff_index = 0;
    }
}       