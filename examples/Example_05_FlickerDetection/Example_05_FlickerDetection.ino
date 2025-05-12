/*
  Using the AMS AS7343 Sensor.

  This example shows how to use the Flicker Detection feature of the AS7343 sensor.
  It sets up the sensor with default settings and prints out the flicker detection
    results to the serial monitor.

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
    Serial.println("AS7343 Example 05 - Flicker Detection");

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

    // Set the AutoSmux to output all 18 channels
    if (mySensor.setAutoSmux(AUTOSMUX_18_CHANNELS) == false)
    {
        Serial.println("Failed to set AutoSmux.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("AutoSmux set to 18 channels.");

    // Enable Flicker Detection
    if (mySensor.enableFlickerDetection() == false)
    {
        Serial.println("Failed to enable flicker detection.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Flicker detection enabled.");

    // Enable Spectral Measurement
    if (mySensor.enableSpectralMeasurement() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement enabled.");

    mySensor.ledOff(); // Turn off the LED for use with flicker detection
    // mySensor.setLedDrive(0); // OPTIONAL Set LED drive to min (0 = 4mA)
    // mySensor.ledOn(); // OPTIONAL Turn on the LED for use with flicker detection
    delay(1000); // Wait for the sensor to stabilize for the first time we enter the loop
}

void loop()
{
    bool fdValid = mySensor.getFdValidStatus(); // Get the flicker detection valid status
    bool fdSaturation = mySensor.getFdSaturationStatus(); // Get the flicker detection saturation status
    uint8_t fdFrequency = mySensor.getFdFrequency(); // Get the flicker detection frequency

    // Check if the flicker detection measurement is valid
    // if it is not valid, print a message and return
    if (fdValid == false)
    {
        Serial.print("Flicker Detection Measurement Invalid");
        Serial.println();
        delay(1000);
        return;
    }

    // Check if the flicker detection measurement is saturated
    // if it is saturated, print a message and return
    if (fdSaturation == true)
    {
        Serial.print("Flicker Detection Saturation Detected");
        Serial.println();
        delay(1000);
        return;
    }

    // if the flicker detection measurement is valid and not saturated,
    // print the flicker detection frequency

    if(fdValid == true && fdSaturation == false)
    {
        if (fdFrequency == 0) // if getFdFrequency() returns 0, no frequency detected
            Serial.print("No Flicker Detected");
        else
        {
            Serial.print("Flicker Detected at frequency: ");
            Serial.print(fdFrequency);
            Serial.print("Hz");
        }
        Serial.println();
    }

    delay(1000);
}
