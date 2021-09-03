#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>
 
// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x46);

 
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
  Wire.begin();
  //pwm.begin();
  //pwm.setPWMFreq(1000);  // This is the maximum PWM frequency
 
Wire.setClock(100000);
 
}

 void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.println("0");
      Serial.println(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.println("Unknown error at address 0x");
      if (address<16)
        Serial.println("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.print("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}
/*
void loop() { //POMPE 5 = LED 9 = PIN 16
  Wire.tr
  for(int i = 6; i < 23; i++)
  {
      pwm.setPWM(i, 4096, 0);
  }

  //delay(5000);
    //pwm.setPWM(16, 0, 4096);
}*/
