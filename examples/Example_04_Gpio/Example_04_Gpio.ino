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

    // Reset the device
    // This is not required, but if the device was previously used, then we need
    // to reset it to ensure it's powered down before we adjust the settings.
    if (mySensor.reset() == false)
    {
        Serial.println("Failed to reset the device.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Device reset.");

    delay(10);

    // Power on the device
    if (mySensor.powerOn() == false)
    {
        Serial.println("Failed to power on the device.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Device powered on.");

        // Enable Spectral Measurement
        if (mySensor.spectralMeasurementEnable() == false)
        {
            Serial.println("Failed to enable spectral measurement.");
            Serial.println("Halting...");
            while (1)
                ;
        }
        Serial.println("Spectral measurement enabled.");

    // // Set the AutoSmux to output 6 channels
    // // Using the AutoSmux set to 6 channels, and the interrupt channel set to 0,
    // // the spectral band FZ (450nm, aka BLUE) will be used for the interrupt.
    // if (mySensor.setAutoSmux(AUTOSMUX_6_CHANNELS) == false)
    // {
    //     Serial.println("Failed to set AutoSmux.");
    //     Serial.println("Halting...");
    //     while (1)
    //         ;
    // }
    // Serial.println("AutoSmux set to 6 channels.");

    // // Set the GPIO mode to input
    // if (mySensor.setGpioMode(AS7343_GPIO_MODE_INPUT) == false)
    // {
    //     Serial.println("Failed to set GPIO mode.");
    //     Serial.println("Halting...");
    //     while (1)
    //         ;
    // }
    // Serial.println("GPIO mode set to input.");

        // Set the GPIO mode to output
        if (mySensor.setGpioMode(AS7343_GPIO_MODE_OUTPUT) == false)
        {
            Serial.println("Failed to set GPIO mode.");
            Serial.println("Halting...");
            while (1)
                ;
        }
        Serial.println("GPIO mode set to output.");

        // // Enable wait time
        // if (mySensor.enableWaitTime() == false)
        // {
        //     Serial.println("Failed to enable wait time.");
        //     Serial.println("Halting...");
        //     while (1)
        //         ;
        // }
        // Serial.println("Wait time enabled.");



    //     // Set the wait time to 5.56ms (value of "2" in the WTIME register)
    // // It is necessary for WTIME to be sufficiently long for spectral integration 
    // // and any other functions to be completed within the period. The device will 
    // // warn the user if the timing is configured incorrectly. If WTIME is too 
    // // short, then SP_TRIG in register STATUS4 (ADDR: 0xBC) will be set to “1”.
    // // default integration time is 2.78ms.
    // if (mySensor.setWaitTime(255) == false)
    // {
    //     Serial.println("Failed to set wait time.");
    //     Serial.println("Halting...");
    //     while (1)
    //         ;
    // }
    // Serial.println("Wait time set to 5.56ms.");

    // // Verify Wait time was written correctly by printing it to terminal
    // Serial.print("Wait time set to: ");
    // Serial.println(mySensor.getWaitTime());



    // // Enable Spectral Measurement
    // if (mySensor.spectralMeasurementEnable() == false)
    // {
    //     Serial.println("Failed to enable spectral measurement.");
    //     Serial.println("Halting...");
    //     while (1)
    //         ;
    // }
    // Serial.println("Spectral measurement enabled.");

    // mySensor.ledOff();

    // read the GPIO register and print it to terminal
    uint8_t registerValue; // Create a variable to hold the register value
    if (mySensor.readRegister(0x6B, registerValue) == false)
    {
        Serial.println("Failed to read GPIO register.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.print("GPIO register value: 0x");
    Serial.print(registerValue, HEX);
    Serial.print(" (0b");
    Serial.print(registerValue, BIN);
    Serial.print(")\n");
}

void loop()
{
    //mySensor.ledOn();

    // Set the GPIO to LOW
    if (mySensor.setGpioOutput(AS7343_GPIO_OUTPUT_LOW) == false)
    {
        Serial.println("Failed to set GPIO output to LOW.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("GPIO output set to LOW.");
    delay(1000);

        // read the GPIO register and print it to terminal
        uint8_t registerValue; // Create a variable to hold the register value
        if (mySensor.readRegister(0x6B, registerValue) == false)
        {
            Serial.println("Failed to read GPIO register.");
            Serial.println("Halting...");
            while (1)
                ;
        }
        Serial.print("GPIO register value: 0x");
        Serial.print(registerValue, HEX);
        Serial.print(" (0b");
        Serial.print(registerValue, BIN);
        Serial.print(")\n");

    // Arduino digital pin 7 is connected to GPIO
    pinMode(7, INPUT_PULLUP);
    int gpioStatus = digitalRead(7);
    Serial.print("D7 Status: ");
    if (gpioStatus == HIGH)
    {
        Serial.println("HIGH");
    }
    else
    {
        Serial.println("LOW");
    }
    delay(1000);

    // Set the GPIO to HIGH
    if (mySensor.setGpioOutput(AS7343_GPIO_OUTPUT_HIGH) == false)
    {
        Serial.println("Failed to set GPIO output to HIGH.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("GPIO output set to HIGH.");
    delay(1000);

        // read the GPIO register and print it to terminal
        //uint8_t registerValue; // Create a variable to hold the register value
        if (mySensor.readRegister(0x6B, registerValue) == false)
        {
            Serial.println("Failed to read GPIO register.");
            Serial.println("Halting...");
            while (1)
                ;
        }
        Serial.print("GPIO register value: 0x");
        Serial.print(registerValue, HEX);
        Serial.print(" (0b");
        Serial.print(registerValue, BIN);
        Serial.print(")\n");

    // Read Arduino pin D7 and print the status
    gpioStatus = digitalRead(7);
    Serial.print("D7 Status: ");
    if (gpioStatus == HIGH)
    {
        Serial.println("HIGH");
    }
    else
    {
        Serial.println("LOW");
    }

    delay(10000); // Wait 10 seconds

    // while(mySensor.getSpectralValidStatus() == false)
    // {
    //     Serial.print(".");
    //     delay(1);
    // }
    // Serial.println("valid data ready ");

    // // print the GPIO input status
    // Serial.print("GPIO Input Status: ");
    // if (mySensor.getGpioInputStatus() == true)
    // {
    //     Serial.print("HIGH ");
    // }
    // else
    // {
    //     Serial.print("LOW ");
    // }


    // // Get spectral valid status to ensure the data is valid
    // // if it fails, print a failure message and continue
    // if (mySensor.getSpectralValidStatus() == false)
    // {
    //     Serial.println("Spectral data is not valid.");
    // }
    // else
    // {
    //     // Read all data registers
    //     // if it fails, print a failure message and continue
    //     if (mySensor.readAllSpectralData() == false)
    //     {
    //         Serial.println("Failed to read spectral data.");
    //     }

    //     //mySensor.ledOff();

    //     // Print the data from the 6 channels (note, we are using AutoSmux set to 6 channels)
    //     // The channels are defined in the datasheet as FZ, FY, FXL, NIR, 2xVIS, FD
    //     for(int channel = 0; channel <6; channel++)
    //     {
    //         Serial.print(mySensor.getChannelData(channel));
    //         Serial.print(",");
    //     }
    // }



    Serial.println();

}
