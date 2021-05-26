/*
 * LidarXV11.cpp
 *
 *  Created on: 18 avr. 2019
 *      Author: robot
 */

#include "LidarXV11.h"

#define SERIAL_DEBUG Serial2

LidarXV11::LidarXV11() : speed(0){
	state = WAIT_START;
	packet = {0};
	packet_available = false;
	tmp = 0;
	c = 0;
	tmpck = 0;
	ck = 0;
	chk32 = 0;
	checksum = 0;
}

LidarXV11::~LidarXV11() {
}

int LidarXV11::update(uint8_t byte) {
	SERIAL_DEBUG.println(byte, HEX);
	return 0;


	int ret = 0;
	uint16_t checksum_rx;
	switch (state) {
	case WAIT_START:
		if (byte == 0xFA){
			state = WAIT_INDEX;
			SERIAL_DEBUG.println();
			ck = 0;
			chk32 = 0;
		}
		break;
	case WAIT_INDEX:
		SERIAL_DEBUG.print(" wi ");
		if (byte <= 0xF9 && byte >= 0xA0) {
			packet.index = (int)byte - 0xA0;
			packet_available = false;
			state = WAIT_SPEED_L;
		}
		else{
			state = WAIT_START;
		}
		break;
	case WAIT_SPEED_L:
	SERIAL_DEBUG.print(" wsl ");
		tmp = byte;
		state = WAIT_SPEED_H;
		break;
	case WAIT_SPEED_H:
	SERIAL_DEBUG.print(" wsh ");
		packet.speed = ((byte << 8) | tmp) / 64;
		c = 0;
		state = READ_DATA_0;
		break;
	case READ_DATA_0:
	SERIAL_DEBUG.print(" rd0 ");
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(0);
			c = 0;
			state = READ_DATA_1;
		}
		break;
	case READ_DATA_1:
	SERIAL_DEBUG.print(" rd1 ");
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(1);
			c = 0;
			state = READ_DATA_2;
		}

		break;
	case READ_DATA_2:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(2);
			c = 0;
			state = READ_DATA_3;
		}
		break;
	case READ_DATA_3:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(3);
			c = 0;
			state = WAIT_CHECKSUM_L;
		}
		break;
	case WAIT_CHECKSUM_L:
		checksum = (chk32 & 0x7FFF) + (chk32 >> 15);
		checksum = checksum & 0x7FFF;

		tmp = byte;
		state = WAIT_CHECKSUM_H;
		break;
	case WAIT_CHECKSUM_H:
		checksum_rx = (byte << 8) | tmp;
		if (checksum == checksum_rx){
			packet_available = true;
			speed = packet.speed;
			if(packet.index == 89) {
				ret = 1;
			}
			if(true || (packet.index >= 2 && packet.index <15)) {
				display_package(&packet);
			}
			
		}
		else{
			
		//	SERIAL_DEBUG.printf("%d LIDAR CHECKSUM INVALID : %d | %d\n",packet.index , checksum, checksum_rx);
		}
		state = WAIT_START;
		break;
	default:
		//SERIAL_DEBUG.println("AAAAAAH");
		break;
	}
	if (ck % 2 == 0){
		tmpck = byte;
	}
	else{
		uint16_t d = tmpck + (byte << 8);
		chk32 = (chk32 << 1) + d;
	}
	ck++;

	SERIAL_DEBUG.printf("%02X ", byte);

	return ret;
}

void LidarXV11::display_package(struct Package_Data* p) {
	// SERIAL_DEBUG.print(p->index);
	// SERIAL_DEBUG.print("   ");
	// SERIAL_DEBUG.print(p->speed);
	// SERIAL_DEBUG.print(" | ");
	for (int i = 0; i < 4; i++ ){
		SERIAL_DEBUG.print(p->index);
		SERIAL_DEBUG.print("   ");
		SERIAL_DEBUG.print(p->speed);
		SERIAL_DEBUG.println(" | ");
		//SERIAL_DEBUG.printf("%d: dst: %d, inv: %d, war:%d, str: %d\n", (p->index)  * 4 + i, p->distance[i], p->invalid[i], p->warning[i], p->strength[i]);
	}
	Serial.println();
}

void LidarXV11::read_data(int i) {
	packet.distance[i] = ((0b00111111 & data[1]) << 8) | data[0];
	//Serial.print(packet.distance[i]);
	//Serial.print(" ");
	packet.invalid[i] = (data[1] & 0b10000000);
	packet.warning[i] = (data[1] & 0b01000000);
	packet.strength[i] = (data[3] << 8) | data[2];
	distance_angle[packet.index  * 4 + i] = packet.distance[i];
	/*if (packet.invalid[i]){
		distance_angle[(packet.index - 0xA0)  * 4 + i] = 2000;
	}*/
	//Serial.print((packet.index - 0xA0)  * 4 + i);
	//Serial.print(" ");
	valid_angle[packet.index  * 4 + i] = !packet.invalid[i];
	//Serial.println(valid_angle[(packet.index - 0xA0)  * 4 + i]);

}

int LidarXV11::get_distance(int angle){
	return distance_angle[angle];
}

bool LidarXV11::is_valid(int angle){
	return valid_angle[angle];
}

void LidarXV11::init() {

}
