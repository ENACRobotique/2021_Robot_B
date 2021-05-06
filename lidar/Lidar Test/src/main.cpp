#include <Arduino.h>
#include "lidar/LidarXV11.h"
#include "lidar/InterfaceLidar.h"
//#include <MemoryFree.h>

InterfaceLidar xv11 = InterfaceLidar();
//LidarXV11 xv11 = LidarXV11();


int ledPin = 13;
int last_update = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); //allumer la led sur la carte
  digitalWrite(ledPin, HIGH);
  Serial.begin(115200);
  //while (!Serial) {
    //wait for serial port to connect. Needed for native USB
  //}
  Serial.println("USB Serial working.");
  Serial1.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()) {
    uint8_t c = Serial1.read();
    xv11.update_and_calc(c);
    //xv11.update(c);
    //if (xv11.is_packet_available()){
		//	struct Package_Data packet = xv11.get_packet();
		//	if (packet.index == 110 / 4 + 0xA0){
		//		xv11.display_package(&packet);
		//	}
		//}
  }

  int* buffer_dist = xv11.get_buffer_dist();
  int* raw_dist = xv11.get_raw_dist();
  int* expec_dist = xv11.get_expected_dist();

  if (millis() - last_update >= 100){
    last_update = millis();
    for (int i = 0; i<360; i++){
      Serial.print("l ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(raw_dist[i]);
      Serial.print(" ");
      Serial.print(buffer_dist[i]);
      Serial.print(" ");
      Serial.println(expec_dist[i]);
    }
  }
}
