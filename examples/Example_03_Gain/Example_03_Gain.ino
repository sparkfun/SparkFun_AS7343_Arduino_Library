/*
  Using the AMS AS7343 Sensor.

  This example shows how to setup the AS7343 sensor with a specific Spectral 
  Engines Gain Setting (aka "AGAIN").
  
  It Checks if serial message has come in from user
  If it's a "-" then reduce the gain by 1 setting it to the next lower value
  If it's a "+" then increase the gain by 1 setting it to the next higher value

  It then prints out all the spectral data from the sensor.

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
#include <math.h> // used for calculating gain values (when printing to serial)

SfeAS7343ArdI2C mySensor;

// user input
char userInput;

// array of gain settings using the enum typedef in sfDevAS7343.h
sfe_as7343_again_t gainSettings[] = {
    AGAIN_0_5,
    AGAIN_1,
    AGAIN_2,
    AGAIN_4,
    AGAIN_8,
    AGAIN_16,
    AGAIN_32,
    AGAIN_64,
    AGAIN_128,
    AGAIN_256,
    AGAIN_512,
    AGAIN_1024,
    AGAIN_2048};

// Variable to hold current user set gain index (position within the array)
int gainSettingIndex = 9; // default to 256x gain

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(100);
    };
    Serial.println("AS7343 Example 03 - Gain Setting");

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

    // Set the gain to 512x
    // Note, the default fain is 256x.
    if (mySensor.setAgain(AGAIN_512) == false)
    {
        Serial.println("Failed to set gain.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Gain set to 512x.");

    // Enable Spectral Measurement
    if (mySensor.enableSpectralMeasurement() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement enabled.");
}

void loop()
{
    // Check if serial message has come in from user
    // If it's a "-" then reduce the gain by 1 setting it to the next lower value
    // If it's a "+" then increase the gain by 1 setting it to the next higher value

    if(Serial.available())
    {
        userInput = Serial.read();
        if (userInput == '+' || userInput == '-')
        {
            updateGainSetting(userInput);
        }
    }

    //mySensor.ledOn();
    delay(100);

    // Read all data registers
    // if it fails, print a failure message and continue
    if (mySensor.readSpectraDataFromSensor() == false)
    {
        Serial.println("Failed to read spectral data.");
    }

    mySensor.ledOff();

    // Print the data from all the channels
    for(int channel = 0; channel <17; channel++)
    {
        Serial.print(mySensor.getChannelData(channel));
        Serial.print(",");
    }

    Serial.println();

    delay(500);
}

// update gain setting based on user input
// Note, we must first disable measurements, set the gain, then re-enable measurements
// to change the gain setting
void updateGainSetting(char input)
{
    // Disable spectral measurement
    if (mySensor.disableSpectralMeasurement() == false)
    {
        Serial.println("Failed to disable spectral measurement.");
        return;
    }

    // Update gain setting based on user input
    if (input == '+')
    {
        gainSettingIndex++;
        if (gainSettingIndex > 12)
            gainSettingIndex = 12; // max gain is 2048x
    }
    else if (input == '-')
    {
        gainSettingIndex--;
        if (gainSettingIndex < 0)
            gainSettingIndex = 0; // min gain is 0.5x
    }

    // Set the new gain setting
    if (mySensor.setAgain(gainSettings[gainSettingIndex]) == false)
    {
        Serial.println("Failed to set gain.");
        return;
    }

    // Re-enable spectral measurement
    if (mySensor.enableSpectralMeasurement() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        return;
    }

    printGainValue(gainSettings[gainSettingIndex]);
}

// Print gain value to the serial monitor
void printGainValue(sfe_as7343_again_t gainSetting)
{
    // To convert from gainSetting to gain value, we use the formula:
    // gainValue = 2^(gainSetting - 1)
    float gainValue = pow(2, (gainSetting-1));
    
    Serial.print("Gain Value: ");
    Serial.println(gainValue);
}
