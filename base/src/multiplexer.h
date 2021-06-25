#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
   
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();

#define SENSOR_NUMBER 2 //nombre de capteurs connectés au multiplexeur
#define TCAADDR 0x70
    
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X); //Attention modif à prévoir dans la library pour les capteurs chinois
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X); //Attention modif à prévoir dans la library pour les capteurs chinois


Adafruit_TCS34725 tcs[SENSOR_NUMBER] = {
    tcs0,
    tcs1
  };

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
    Serial.begin(115200);
    Serial.println("hello");

    for(int i=0; i< SENSOR_NUMBER; i++){
      tcaselect(i);
      delay(500);
        if (tcs[i].begin()) {
          Serial.print("Found sensor on I2C port #");
          Serial.println(i);
        } else {
          Serial.print("No TCS34725 found on port #");
          Serial.println(i);
          //while (1);
      }
    }
  }
  
  // Now we're ready to get readings

void loop(void) {
  for(int i=0; i< SENSOR_NUMBER; i++){
    tcaselect(i);
    uint16_t r, g, b, c, colorTemp, lux;
    
    tcs[i].getRawData(&r, &g, &b, &c);
    colorTemp = tcs[i].calculateColorTemperature(r, g, b);
    lux = tcs[i].calculateLux(r, g, b);

    Serial.print("Sensor #");Serial.print(i); Serial.print(" --- ");
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
    delay(1000);
  }