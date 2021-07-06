#include "Arduino.h"
#include "params.h"
#include "controlServo.h"
#include "actuatorSupervisor.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "Adafruit_TCS34725.h"
#include "ai/MatchDirector.h"

namespace ActuatorSupervisor
{

	ControlServo armServos[5];
    ControlServo otherServos[2]; //[0] = Pavillon, [1] = tige horizontale

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(LED_DRIVER_ADDRESS, Wire);

    Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X); //Attention modif à prévoir dans la library pour les capteurs chinois
    Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

    bool pavillon_deployed = false;

    void init()
    {
        delay(100);
        Wire.begin();
        pwm.begin();
        pwm.setPWMFreq(SERVO_FREQ);
        delay(100);
        //arms servos
        
        /*for (int i = 0; i < 5; i++)
        {
            armServos[i].defInitAngle(150);
            armServos[i].init(servo_nb_to_pin(i), &pwm);
            switch_pompe(false, i);
            switch_ev(false, i);
        }*/

        for (int i = 2; i < 5; i++)
        {
            armServos[i].defInitAngle(150);
            armServos[i].init(servo_nb_to_pin(i), &pwm);
            switch_pompe(false, i);
            switch_ev(false, i);
        }

        //other servos
        otherServos[0].defInitAngle(SERVO_PAV_ANGLE_RTRCTED);
        //otherServos[0].init(SERVO_PAV, NULL); 
        otherServos[0].init(SERVO1, &pwm);
        
        otherServos[1].defInitAngle(SERVO_BAR_ANGLE_RTRCTED);
        //otherServos[1].init(SERVO_BAR, NULL); 
        otherServos[1].init(SERVO2, &pwm); 

        //TODO : pinMode nécessaire ou non
        //pinMode(POMPE, OUTPUT);
        //pinMode(VANN, OUTPUT);

        //multiplexers
        //delay(10);
        //pwm.begin();
        //pwm.setPWMFreq(PWM_FREQUENCY);    
        SerialDebug.println("init done for actuatorSupervisor ! ");
    }

    void deploy_pav()
    {
        if(pavillon_deployed == false)
        {
            MatchDirector::addScore(10);
            otherServos[0].moveServo(SERVO_PAV_ANGLE_DPLOYED);
            pavillon_deployed = true;
        }

        //SerialCtrl.println("pavillon - ordre de déploiement");
    }
    void retract_pav()
    {
        otherServos[0].moveServo(SERVO_PAV_ANGLE_RTRCTED);
        pavillon_deployed = false;
    }
    void deploy_bar()
    {
        otherServos[1].moveServo(SERVO_BAR_ANGLE_DPLOYED);
    }
    void retract_bar()
    {
        otherServos[1].moveServo(SERVO_BAR_ANGLE_RTRCTED);
    }

    void switch_pompe(bool isOn, int pompe)
    {
        SerialCtrl.println("ENABLE POMPE NOT TESTED");
        int start_pwm = (isOn) ? 4096 : 0;
        int end_pwm = (isOn) ? 0 : 4096;
        pwm.setPWM(pompe_nb_to_pin(pompe), start_pwm, end_pwm);
        //int pin = pompe_nb_to_pin(pompe);
    }
    void switch_ev(bool isOn, int ev)
    {
        SerialCtrl.println("ENABLE EV NOT TESTED");
        int start_pwm = (isOn) ? 4096 : 0;
        int end_pwm = (isOn) ? 0 : 4096;
        pwm.setPWM(ev_nb_to_pin(ev), start_pwm, end_pwm);
    }
    int servo_nb_to_pin(int servo) 
    /* return 0 if servo_nb not between 0 & 4 included */
    {
        switch (servo)
        {
        case 0:
            return SERVO1;
        case 1:
            return SERVO2;
        case 2:
            return SERVO3;
        case 3:
            return SERVO4;
        case 4:
            return SERVO5;
        default:
            return 0;
        }
    }
    int pompe_nb_to_pin(int pompe) 
    /* return 0 if servo_nb not between 1 & 5 included */
    {
        switch (pompe)
        {
        case 0:
            return POMPE1;
        case 1:
            return POMPE2;
        case 2:
            return POMPE3;
        case 3:
            return POMPE4;
        case 4:
            return POMPE5;
        default:
            return 0;
        }
    }

    int ev_nb_to_pin(int ev) 
    /* return 0 if servo_nb not between 1 & 5 included */
    {
        switch (ev)
        {
        case 0:
            return EV1;
        case 1:
            return EV2;
        case 2:
            return EV3;
        case 3:
            return EV4;
        case 4:
            return EV5;
        default:
            return 0;
        }
    }



    void tcaselect(uint8_t i) {
    if (i > 7) return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();  
    }

    CupColor get_color(int sensor_nb) {
        uint16_t r, g, b, c, colorTemp, lux;
        uint8_t sensor_nb_casted = (uint8_t) sensor_nb;
        tcaselect(sensor_nb_casted);
        //tcaselect(sensor_nb_casted);
        
        switch (sensor_nb)
        {
            case 0:
                tcs0.begin();
                tcs0.getRawData(&r, &g, &b, &c);

                break;
            
            default:
            SerialCtrl.println("cup color not implemented !!");
                break;
        }

        SerialCtrl.print("sensor number # with color g and r: #");
        SerialCtrl.print(sensor_nb);
        SerialCtrl.print(g);
        SerialCtrl.println(r);
        if(g >= 5000.f)
        {
            return CupColor::GREEN;
        }
        else if (r >= 5000.f)
        {
            return CupColor::RED;
        }
        else
        {
            return CupColor::NONE;
        }
        



    /*
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
    */
}  

}

/*

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");

  pwm.begin();
  pwm.setPWMFreq(1000);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

void loop() {
  // Drive each pin in a 'wave'
  for (uint8_t pin=0; pin<16; pin++) {
    pwm.setPWM(pin, 4096, 0);       // turns pin fully on
    delay(100);
    pwm.setPWM(pin, 0, 4096);       // turns pin fully off
  }
}

*/

