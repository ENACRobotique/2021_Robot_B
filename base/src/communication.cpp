#include "communication.h"
#include "Arduino.h"
#include <stdlib.h>
#include "motorControl.h"
#include "navigator.h"
#include "odometry.h"
#include "FsmSupervisor.h"
#include "./stateMachine/DeployFrontServo.h"
#include "params.h"

 void findSpaces (char string[50],int a, int pointTab){
    for (int k=0,k<4,k++){
        (*pointTab)[i] = -1
    }
    for (int i=0,i<a,i++){
        if (string[i] == ' '){
            (*pointTab)[i] = i
        }
    }
}
int isName (char string[50], char NOM[10], int lN, int pointTabSpaces){
    int indDebNom = (*pointTabSpaces)[0]+1;
    int LNomMessage = (*pointTabSpaces)[1] - indDebNom;
    int result = 0;
    if (LNomMessage == lN){
        result = 1;
        for (int k = 0, k<lN, k++){
            if (NOM[k] != string [k+indDebNom]){
                result = 0;
            };
        };
    };
    return result;
};
#define COM_DEBUG
struct Message {
    pointFonct pF,
    char[10] val1,
    char[10] val2,
    char[10] val3
    };
void executeOrder (Message m){
    (*m.pF)(m.val1,m.val2, m.val3);
}
namespace Communication {
    
    
    static void parse_data();
    char Nom[5]]; 

    char buffer[50];
    int buff_index=0;
    void update() {
        int a;
        a = SerialCtrl.available();
        #ifdef IHM
            SerialCtrl.print("P R2 "); 
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
                   parse_data(a);
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

    static void parse_data(int a){
        int indSpaces[4]
        findSpaces (buffer, a, &indSpaces)
        if (isName (buffer, "R2", 2, &indSpaces)){

        
            SerialDebug.print(buffer);
            if(buffer[0] == 'E' ) {
                MotorControl::set_cons(0,0);
                navigator.forceStop();
                #ifdef COM_DEBUG
                SerialCtrl.println("Stopped!");
                #endif
            }
            else if(buffer[0] == 'P') {
                char nom[10];
                float x,y;
                int nb = sscanf(buffer, "m %f %f %f", &nom, &x, &y);
                if(nb == 3) {   
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
            };
        };


        buff_index = 0;
    }
}       