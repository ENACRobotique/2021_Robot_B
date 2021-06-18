#include "Wire.h"
#include "debugTest.h"
#include "params.h"


namespace debugTest {

    void scanSerial()
    {
        byte error, address;
        int nDevices;
        
        SerialCtrl.println("Scanning 2...");
        
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
            SerialCtrl.print("I2C device found at address 0x");
            if (address<16)
                SerialCtrl.print("0");
            SerialCtrl.print(address,HEX);
            SerialCtrl.println("  !");
        
            nDevices++;
            }
            else if (error==4)
            {
            SerialCtrl.print("Unknown error at address 0x");
            if (address<16)
                SerialCtrl.print("0");
            SerialCtrl.println(address,HEX);
            }    
        }
        if (nDevices == 0)
            SerialCtrl.println("No I2C devices found\n");
        else
            SerialCtrl.println("done\n");
        }
}

