/*
  Using the AMS AS7343 Sensor.

  This example shows how to setup the AS7343 sensor with an interrupt threshold.
  The interrupt is triggered when the spectral reading on channel 0 exceeds the threshold.

  Using AutoSmux set to 6 channels, and the interrupt channel set to 0,
  the spectral band FZ (450nm, aka BLUE) will be used for the interrupt.

  By: Pete Lewis
  SparkFun Electronics
  Date: 2025/04/22
  SparkFun code, firmware, and software is released under the MIT License.
    Please see LICENSE.md for further details.

  Hardware Connections:
  IoT RedBoard --> AS7331
  QWIIC --> QWIIC

  Serial.print it out at 115200 baud to serial monitor.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/23220
*/

#include <SparkFun_AS7343.h>

SfeAS7343ArdI2C mySensor;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(100);
    };
    Serial.println("AS7343 Example 04 - GPIO");

    Wire.begin();

    // Initialize sensor and run default setup.
    if (mySensor.begin() == false)
    {
        Serial.println("Sensor failed to begin. Please check your wiring!");
        Serial.println("Halting...");
        while (1)
            ;
    }

    Serial.println("Sensor began.");

    // Power on the device
    if (mySensor.powerOn() == false)
    {
        Serial.println("Failed to power on the device.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Device powered on.");

    // Set the AutoSmux to output 6 channels
    // Using the AutoSmux set to 6 channels, and the interrupt channel set to 0,
    // the spectral band FZ (450nm, aka BLUE) will be used for the interrupt.
    if (mySensor.setAutoSmux(AUTOSMUX_6_CHANNELS) == false)
    {
        Serial.println("Failed to set AutoSmux.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("AutoSmux set to 6 channels.");

    // Set the GPIO mode to input
    if (mySensor.setGpioMode(GPIO_MODE_INPUT) == false)
    {
        Serial.println("Failed to set GPIO mode.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("GPIO mode set to input.");

    // Enable Spectral Measurement
    if (mySensor.spectralMeasurementEnable() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement enabled.");

    // read and print int enable reg to verify settings
    Serial.print("Int Enable Reg: 0x");
    Serial.println(mySensor.readIntEnableReg(), HEX);
    Serial.print("Int Enable Reg: 0b");
    Serial.println(mySensor.readIntEnableReg(), BIN);

    mySensor.ledOff();

}

void loop()
{
    //mySensor.ledOn();

    // Arduino digital pin 7 is connected to GPIO
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    delay(1000);

    // print the GPIO input status
    Serial.print("GPIO Input Status: ");
    if (mySensor.getGpioInputStatus() == true)
    {
        Serial.print("HIGH");
    }
    else
    {
        Serial.print("LOW");
    }


    // Get spectral valid status to ensure the data is valid
    // if it fails, print a failure message and continue
    if (mySensor.getSpectralValidStatus() == false)
    {
        Serial.println("Spectral data is not valid.");
    }

    // Read all data registers
    // if it fails, print a failure message and continue
    if (mySensor.readAllSpectralData() == false)
    {
        Serial.println("Failed to read spectral data.");
    }

    //mySensor.ledOff();

    // Print the data from the 6 channels (note, we are using AutoSmux set to 6 channels)
    // The channels are defined in the datasheet as FZ, FY, FXL, NIR, 2xVIS, FD
    for(int channel = 0; channel <6; channel++)
    {
        Serial.print(mySensor.getChannelData(channel));
        Serial.print(",");
    }

    // Print the spectral interrupt high status
    Serial.print("\t\tIntHighStat: ");
    if (mySensor.getSpectralInterruptHighStatus() == true)
    {
        Serial.print("True");
    }
    else
    {
        Serial.print("False");
    }

    // Print the spectral trigger error status
    Serial.print("\tTrigErrStat: ");
    if (mySensor.getSpectralInterruptHighStatus() == true)
    {
        Serial.print("True");
    }
    else
    {
        Serial.print("False");
    }



    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);

    delay(2000);

    // print the GPIO input status
    Serial.print("GPIO Input Status: ");
    if (mySensor.getGpioInputStatus() == true)
    {
        Serial.print("HIGH");
    }
    else
    {
        Serial.print("LOW");
    }

    Serial.println();

}
