#include <Arduino.h>
#include "lidar/LidarXV11.h"
#include <SoftwareSerial.h>
//#include <MemoryFree.h>

SoftwareSerial lidarSerial(2, 3); //RX, TX

LidarXV11 xv11 = LidarXV11();

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT); // the RX pin
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Serial working");
  lidarSerial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(lidarSerial.available()) {
    uint8_t c = lidarSerial.read();
    xv11.update(c);
    if (xv11.is_packet_available()){
			struct Package_Data packet = xv11.get_packet();
			if (packet.index == 110 / 4 + 0xA0){
				xv11.display_package(&packet);
			}
		}
  }
  //Serial.print("freeMemory()=");
  //Serial.println(freeMemory());

}