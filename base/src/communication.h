
#pragma once
#include "def.pb.h"

int send_odom_report(float pos_x, float pos_y, float pos_theta);
int deserialize_speed_command(SpeedCommand* speedCmd, uint8_t* payload_buf, int lenght);
uint16_t compute_cheksum(uint8_t *buffer, size_t len);