#include <Arduino.h>
#include "lidar/LidarXV11.h"
#include "lidar/InterfaceLidar.h"
//#include <MemoryFree.h>

InterfaceLidar xv11 = InterfaceLidar();

int ledPin = 13;
long previousMillis = 0;
int ledState = LOW;  

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); //led sur la carte
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB
  }
  //Serial.println("USB Serial working.");
  Serial1.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial1.available()) {
    uint8_t c = Serial1.read();
    xv11.update_and_calc(c);
    //if (xv11.is_packet_available()){
		//	struct Package_Data packet = xv11.get_packet();
		//	if (packet.index == 110 / 4 + 0xA0){
		//		xv11.display_package(&packet);
		//	}
		//}
  }

  /*for (int i = 0; i<360; i++){
    Serial.print("Angle: ");
    Serial.print(i);
    Serial.print(" Dist: ");
    Serial.println(xv11.get_distance(i));
  }*/

  // Clignotement de la LED a des fins de vérification
  // Code copié depuis un site random, yoink
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 250) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) ledState = HIGH;
    else ledState = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

}