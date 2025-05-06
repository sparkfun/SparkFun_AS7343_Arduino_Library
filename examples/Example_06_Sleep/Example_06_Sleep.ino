/*
  Using the AMS AS7343 Sensor.

  This example shows how to setup the AS7343 sensor with default settings and
  print out all the spectral data from the sensor, putting it to "sleep" inbetween
  measurements to save power.
  
  Note, the AS7343 datasheet refers to each mode of operation as Sleep, Idle,
  and Active. Although there is no direct control of a power mode, we can turn off
  the Measurement and the Power ON bits in the Enable register to put the device
    into a low power state (~350uA).

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
    Serial.println("AS7343 Example 06 - Sleep");

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
}

void loop()
{
    takeReading(); // Wake up and take a reading from the sensor

    sleepSensor(); // Disables measurement (IDLE) and powers off (SLEEP)

    delay(5000); // Wait 5 seconds to allow reading sleep current if needed.
}


void takeReading()
{
    // First, wake up the sensor from sleep mode by powering it on, setting the 
    // AutoSmux to output all 18 channels, and enabling the spectral measurement.

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

    // Enable Spectral Measurement
    if (mySensor.spectralMeasurementEnable() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement enabled.");

    mySensor.ledOn();
    delay(100);

    // Read all data registers
    // if it fails, print a failure message and continue
    if (mySensor.readAllSpectralData() == false)
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
}

// Put the sensor to sleep by turning off the power and measurement
void sleepSensor()
{
    // Disable Spectral Measurement
    if (mySensor.spectralMeasurementDisable() == false)
    {
        Serial.println("Failed to disable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement disabled.");

    // Power off the device
    if (mySensor.powerOff() == false)
    {
        Serial.println("Failed to power off the device.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Device powered off.");
}