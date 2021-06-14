#include "communication.h"
#include "Arduino.h"
#include <stdlib.h>
#include "motorControl.h"
#include "navigator.h"
#include "odometry.h"
#include "FsmSupervisor.h"
#include "ai/MatchDirector.h"
#include "ai/ActionsList.h"
#include "params.h"
#include "actuatorSupervisor.h"

#include "stateMachine/Recalibration_wall.h"


#define COM_DEBUG

namespace Communication {
    
    
    static void parse_data();

    char buffer[50];
    int buff_index=0;
    void update() {
        int a;
        a = SerialCtrl.available();
        
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
        else if(buffer[0] == 'o') {
            SerialCtrl.print("pos - odometry_motor : ");
            SerialCtrl.print(odometry_motor.get_pos_x());
            SerialCtrl.print("\t");
            SerialCtrl.print(odometry_motor.get_pos_y());
            SerialCtrl.print("\t");
            SerialCtrl.println(odometry_motor.get_pos_theta());
        }
        else if(buffer[0] == '2') {
            SerialCtrl.print("pos - odometry_wheel : ");
            SerialCtrl.print(odometry_wheel.get_pos_x());
            SerialCtrl.print("\t");
            SerialCtrl.print(odometry_wheel.get_pos_y());
            SerialCtrl.print("\t");
            SerialCtrl.println(odometry_wheel.get_pos_theta());
        } 
        else if(buffer[0] == '1') {
            SerialCtrl.print("pos - absolue :  ");
            SerialCtrl.print(MatchDirector::get_abs_x());
            SerialCtrl.print("\t");
            SerialCtrl.println(MatchDirector::get_abs_y());
        } 
        else if(buffer[0] == 't') {
            //in degrees
            float angle;
            int nb = sscanf(buffer, "t %f", &angle);
            if(nb == 1) {
                navigator.turn_to(angle);
            }
        }
        else if(buffer[0] == 'l') { //deploy front servo -> from start to deposit ecocup
            MatchDirector::set_current_action(ActionList::TestStrategieMvtOnly);
        }
        else if(buffer[0] == 'd') { //deploy pavillon
            ActuatorSupervisor::otherServos[1].moveServo(SERVO_PAV_ANGLE_DPLOYED);
        }
        else if(buffer[0] == 'r') { //deploy recalibration
            char wall;
            int nb = sscanf(buffer, "r %c", &wall);
            switch (wall)
            {
            case 'l':
                fsmSupervisor.setNextState(&recalibration_wall_left);
                break;
            case 't':
                fsmSupervisor.setNextState(&recalibration_wall_top);
                break;
            case 'b':
                fsmSupervisor.setNextState(&recalibration_wall_bottom);
                break;
            
            default:
                break;
            }

        }
        else if(buffer[0] == 'a') {
            float x,y;
            int nb = sscanf(buffer, "a %f %f", &x, &y);
            if(nb == 2) {   
                MatchDirector::abs_coords_to(x, y);
                #ifdef COM_DEBUG
                SerialCtrl.print("Moving to ");
                SerialCtrl.print(x);
                SerialCtrl.print("\t");
                SerialCtrl.println(y);
                #endif
            }
        }
        else if(buffer[0] == 'p') { //parking
            char color; //w = white, b = black
            int nb = sscanf(buffer, "p %c", &color);
            MatchDirector::compute_final_point((color == 'w') ? true : false);
        }



        buff_index = 0;
    }
}       