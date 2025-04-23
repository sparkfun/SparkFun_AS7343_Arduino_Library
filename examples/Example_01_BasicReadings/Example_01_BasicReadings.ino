/*
  Using the AMS AS7343 Sensor.

  This example shows how to setup the AS7343 sensor with default settings and
  print out all the spectral data from the sensor.

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
    Serial.println("AS7343 Example 01 - Basic Readings");

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

    // Enable Spectral Measurement
    if (mySensor.spectralMeasurementEnable() == false)
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
    // turn on the LED
    mySensor.ledOn();
    // Wait for 100ms
    delay(100);

    // Read all data registers
      // if it fails, print a failure message and continue
      if (mySensor.readAllSpectralData() == false)
      {
          Serial.println("Failed to read spectral data.");
          return;
      }

    // turn off the LED
    mySensor.ledOff();

    // Print the data from all the channels
    // for(int channel = 0; channel <17; channel++)
    // {
    //     Serial.print(mySensor.getData(channel));
    //     Serial.print(",");
    // }

    // print blue red, green... for testing
    // note, serial plotter in arduino draws lines and the incoming data gets plotted to lines in this order (blue,red,green).

    // FZ (blue) data array position 0
    Serial.print(mySensor.getData(0)); // FZ (blue) data array position 0
    Serial.print(",");

    // F7 (red) data array position 13
    Serial.print(mySensor.getData(13)); // F7 (red) data array position 13
    Serial.print(",");

    // FY (green) data array position 1
    Serial.print(mySensor.getData(1)); // FY (green) data array position 1
    Serial.print(",");



    Serial.println();

    delay(500);
}
