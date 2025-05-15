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

#define INT_HW_READ_PIN 4 // Pin to read the interrupt pin from the AS7343

void setup()
{

    // Set the pin mode for the interrupt pin
    pinMode(INT_HW_READ_PIN, INPUT); // Set the pin to input, the qwiic bob has a pullup resistor

    Serial.begin(115200);
    while (!Serial)
    {
        delay(100);
    };
    Serial.println("AS7343 Example 04 - Interrupt");

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

    // Before we enable measurement, we need to set up the interrupt threshold.
    // This involves four things:
    // 1. Set the spectral threshold channel to channel 0 (FZ)
    // 2. Set the spectral interrupt threshold high to 100
    // 3. Enable and set the amount of Wait Time to >0.
    // 4. Enable the spectral interrupt

    // Enable wait time
    if (mySensor.enableWaitTime() == false)
    {
        Serial.println("Failed to enable wait time.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Wait time enabled.");
    
    // Set the wait time to 5.56ms (value of "2" in the WTIME register)
    // It is necessary for WTIME to be sufficiently long for spectral integration 
    // and any other functions to be completed within the period. The device will 
    // warn the user if the timing is configured incorrectly. If WTIME is too 
    // short, then SP_TRIG in register STATUS4 (ADDR: 0xBC) will be set to “1”.
    // default integration time is 2.78ms.
    if (mySensor.setWaitTime(2) == false)
    {
        Serial.println("Failed to set wait time.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Wait time set to 5.56ms.");

    // Set the spectral threshold channel to channel 0 (FZ)
    if (mySensor.setSpectralThresholdChannel(SPECTRAL_THRESHOLD_CHANNEL_0) == false)
    {
        Serial.println("Failed to set spectral threshold channel.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral threshold channel set to channel 0.");

    // Set the spectral interrupt threshold high to 10
    if (mySensor.setSpectralIntThresholdHigh(10) == false)
    {
        Serial.println("Failed to set spectral interrupt threshold high.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral interrupt threshold high set to 10.");

    // Set Spectral Interrupt Persistence to 1
    // This means that the interrupt will be triggered if the spectral data is 
    // outside the thresholds (above H or below L) for 1 cycle.
    if (mySensor.setSpectralIntPersistence(1) == false)
    {
        Serial.println("Failed to set spectral interrupt persistence.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral interrupt persistence set to 1.");

    // Enable the spectral interrupt
    if (mySensor.enableSpectralInterrupt() == false)
    {
        Serial.println("Failed to enable spectral interrupt.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral interrupt enabled.");

    // Enable Spectral Measurement
    if (mySensor.enableSpectralMeasurement() == false)
    {
        Serial.println("Failed to enable spectral measurement.");
        Serial.println("Halting...");
        while (1)
            ;
    }
    Serial.println("Spectral measurement enabled.");

    // // read and print int enable reg to verify settings
    // Serial.print("Int Enable Reg: 0x");
    // Serial.println(mySensor.readIntEnableReg(), HEX);
    // Serial.print("Int Enable Reg: 0b");
    // Serial.println(mySensor.readIntEnableReg(), BIN);
}

void loop()
{
    //mySensor.ledOn();

    // Get spectral valid status to ensure the data is valid
    // if it fails, print a failure message and continue
    if (mySensor.getSpectralValidStatus() == false)
    {
        Serial.println("Spectral data is not valid.");
    }

    // Read all data registers
    // if it fails, print a failure message and continue
    if (mySensor.readSpectraDataFromSensor() == false)
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

    // Print the spectral channel interrupt status
    Serial.print("\tSpectralIntStat: ");
    if (mySensor.getSpectralChannelInterruptStatus() == true)
    {
        Serial.print("True");
    }
    else
    {
        Serial.print("False");
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
    if (mySensor.getSpectralTriggerErrorStatus() == true)
    {
        Serial.print("True");
    }
    else
    {
        Serial.print("False");
    }

    // Print the status of the interrupt pin read
    Serial.print("\tINT Pin: ");
    bool intPinStatus = digitalRead(INT_HW_READ_PIN);
    if (intPinStatus == HIGH)
    {
        Serial.print("HIGH");
    }
    else
    {
        Serial.print("LOW");
    }

    // If an interrupt is detected (active LOW), print a message to the serial 
    // monitor, and clear the interrupt in the register by writing to the STATUS register
    if (intPinStatus == LOW)
    {
        Serial.println("\tInterrupt detected!");
        delay(3000);
        // Clear the interrupt by writing a 1 to the SINT bit in the STATUS register
        mySensor.clearSpectralChannelInterrupt();
        Serial.println("Interrupt cleared.");
        Serial.println("Move your sensor to lower light levels again to avoid immediate re-triggering.");
        delay(3000);
    }

    Serial.println();

    delay(1000);
}
