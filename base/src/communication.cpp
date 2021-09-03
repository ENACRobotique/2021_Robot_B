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

#include "stateMachine/MoveBar.h"

#define COM_DEBUG

namespace Communication
{

    static void parse_data();

    char buffer[50];
    int buff_index = 0;
    void update()
    {
        int a;
        a = SerialCtrl.available();

        if (a)
        {

            for (int k = 0; k < a; k++)
            {
                char c = SerialCtrl.read();
                //serialCtrl.write(c);
                if (c == '\n')
                {

                    buffer[buff_index] = '\0';
                    //             serialCtrl.write(buffer,i);
                    parse_data();
                    //value=atoi(buffer);
                    buff_index = 0;
                }
                else if (c == '\r')
                {
                }
                else
                {
                    buffer[buff_index] = c;
                    buff_index++;
                }
            }
        }
    }

    static void parse_data()
    {
        if (buffer[0] == 'D')
        { //demande de description
            sendDescription();
        }
        else if (buffer[0] == 'E')
        {
            MotorControl::set_cons(0, 0);
            navigator.forceStop();

            buff_index = 0;
        }
        else if (buffer[0] == 'A')
        { //Actionneur
            char nom[10];
            char act[10];
            int val;
            int nb = sscanf(buffer, "A %s %s %i", nom, act, &val);
            if (nb == 3)
            {
                if (act[0] == 'D')
                { //Pavillon
                    if (val == 0)
                    {
                        ActuatorSupervisor::retract_pav();
                    }
                    else if (val == 1)
                    {
                        ActuatorSupervisor::deploy_pav();
                    }
                }
                else if (act[0] == 'B')
                { //Barre
                    if (val == 0)
                    {
                        ActuatorSupervisor::retract_bar();
                    }
                    else if (val == 1)
                    {
                        ActuatorSupervisor::deploy_bar();
                    }
                }
            }
        }
        else if (buffer[0] == 'O')
        { //Position (+orientation mais on ne traite pas)
            char nom[10];
            int x, y;
            float theta;
            int nb = sscanf(buffer, "O %s %i %i %f", nom, &x, &y, &theta);
            if (nb == 4)
            {
                MatchDirector::abs_coords_to(x, y);
            }
        }
        else if (buffer[0] == 'P')
        { //Position
            char nom[10];
            int x, y;
            int nb = sscanf(buffer, "P %s %i %i", nom, &x, &y);
            if (nb == 3)
            {
                MatchDirector::abs_coords_to(x, y);
            }
        }
        else if (buffer[0] == 'S')
        { //Vitesse
            char nom[10];
            int vx, vtheta;
            int nb = sscanf(buffer, "S %s %i 0 %i", nom, &vx, &vtheta);
            if (nb == 3)
            {
                MotorControl::set_cons(vx * 100, vtheta);
            }
        }
    }
    void sendPosition()
    {
        float full_pos[3] = {MatchDirector::get_abs_x(), MatchDirector::get_abs_y(), odometry_wheel.get_pos_theta()};
        SerialCtrl.print("R ");
        SerialCtrl.print(NOM_ROBOT);
        SerialCtrl.print(' ');
        SerialCtrl.print(full_pos[0]);
        SerialCtrl.print(' ');
        SerialCtrl.print(full_pos[1]);
        SerialCtrl.print(' ');
        SerialCtrl.print(full_pos[2]);
        SerialCtrl.println(' ');
    }
    void sendDescription()
    {
        SerialCtrl.print("B ");
        SerialCtrl.print(NOM_ROBOT);
        SerialCtrl.println(" DRAPEAU 0 1 1 RW °");
        SerialCtrl.print("B ");
        SerialCtrl.print(NOM_ROBOT);
        SerialCtrl.println(" BARRE 0 1 1 RW cm");
    }

}
