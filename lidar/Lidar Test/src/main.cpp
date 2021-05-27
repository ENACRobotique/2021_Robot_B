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
  //Serial.begin(115200);
  Serial2.begin(115200);
  //while (!Serial) {
    //wait for serial port to connect. Needed for native USB
  //}
  //Serial.println("USB Serial working.");
  Serial1.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()) {
    uint8_t c = Serial1.read();
    Serial2.println(c, HEX);
    //int turn = xv11.update_and_calc(c);


  // bool* valids = xv11.get_valids();
  // bool* inzone_dist = xv11.get_inzones();
  // int* true_ang = xv11.get_trueang();

  // if (millis() - last_update >= 150 && turn){
  //   last_update = millis();
  //   for (int i = 0; i<360; i++){
  //     //message de point
  //     Serial.print("l ");
  //     Serial.print(true_ang[i]);
  //     Serial.print(" ");
  //     Serial.print(xv11.lidar.get_distance(i));
  //     Serial.print(" ");
  //     Serial.print(valids[i]);
  //     Serial.print(" ");
  //     Serial.print(inzone_dist[i]);
  //     Serial.print(" ");
  //     Serial.print(xv11.get_truexs()[i]);
  //     Serial.print(" ");
  //     Serial.println(xv11.get_trueys()[i]);
  //   }
  //   //message de vitesse moteur
  //     Serial.print("s ");
  //     Serial.println((int)xv11.lidar.getSpeed());
  // }


    //xv11.update(c);
    //if (xv11.is_packet_available()){
		//	struct Package_Data packet = xv11.get_packet();
		//	if (packet.index == 110 / 4 + 0xA0){
		//		xv11.display_package(&packet);
		//	}
		//}
  }


}
