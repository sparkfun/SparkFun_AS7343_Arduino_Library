/*
  Using the AMS AS7343 Sensor.

  This example shows how to setup the AS7343 sensor with the SparkFun Web Serial
  Bar Graphs Demo. It will print out the spectral data from the sensor in a format
    that can be read by the web terminal and displayed as bar graphs.

    Find the web terminal demo code here:
    https://github.com/sparkfunX/WebTerminalDemo/tree/bar-graph-meters

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
    Serial.println("AS7343 Example 07 - Web Terminal Bar Graphs");

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
    mySensor.ledOn();
    delay(100);

    // Read all data registers
    // if it fails, print a failure message and continue
    if (mySensor.readAllSpectralData() == false)
    {
        Serial.println("Failed to read spectral data.");
    }

    //mySensor.ledOff();


    char buffer[100];

    // fill buffer with the channel data in the correct order
    // The order is important, as the web terminal will use this order to display the bar graphs.
    // F1, F2, FZ, F3, F4, F5, FY, FXL, F6, F7, F8, VIS, NIR
    sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
           mySensor.getChannelData(CH_PURPLE_F1_405NM),
           mySensor.getChannelData(CH_DARK_BLUE_F2_425NM),
           mySensor.getChannelData(CH_BLUE_FZ_450NM),
           mySensor.getChannelData(CH_LIGHT_BLUE_F3_475NM),
           mySensor.getChannelData(CH_BLUE_F4_515NM),
           mySensor.getChannelData(CH_GREEN_F5_550NM),
           mySensor.getChannelData(CH_GREEN_FY_555NM),
           mySensor.getChannelData(CH_ORANGE_FXL_600NM),
           mySensor.getChannelData(CH_BROWN_F6_640NM),
           mySensor.getChannelData(CH_RED_F7_690NM),
           mySensor.getChannelData(CH_DARK_RED_F8_745NM),
           mySensor.getChannelData(CH_VIS_1),
           mySensor.getChannelData(CH_NIR_855NM));

    Serial.print(buffer);

    delay(100);
}
