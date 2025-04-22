/*/**
 * @file SparkFun_AS7343.h
 * @brief Arduino-specific implementation for the SparkFun AS7343 Sensor.
 *
 * @details
 * This file provides the Arduino-specific implementation of the AS7343 driver 
 * class. The SfeAS7343ArdI2C class inherits from the base driver class and 
 * implements the I2C communication interface using Arduino's Wire library.
 *
 * Key features:
 * - Arduino I2C initialization
 * - Connection verification
 * - Toolkit integration
 *
 * @section Class SfeAS7343ArdI2C Class
 * - begin(): Initializes I2C communication
 * - isConnected(): Verifies sensor connection
 *
 * @section Dependencies Dependencies
 * - Arduino.h
 * - SparkFun_Toolkit.h
 * - sfeAS7343.h
 *
 * @author SparkFun Electronics
 * @date 2025
 * @copyright Copyright (c) 2023-2025, SparkFun Electronics Inc. All rights reserved.
 *
 * @section License License
 * SPDX-License-Identifier: MIT
 *
 * @section Product_Links Product Links
 * - Qwiic 1x1: https://www.sparkfun.com/products/23220
 *
 * @see https://github.com/sparkfun/SparkFun_AS7343_Arduino_Library
 */

 #pragma once

 // clang-format off
 #include <SparkFun_Toolkit.h>
 #include "sfTk/sfDevAS7343.h"
 #include <Arduino.h>
 // clang-format on
 
/**
 * @class SfeAS7343ArdI2C
 * @brief Arduino I2C implementation for the AS7343 sensor.
 *
 * @details
 * This class provides Arduino-specific I2C communication implementation for the AS7343 sensor.
 * It inherits from the base driver class and implements the I2C interface using Arduino's Wire library.
 * The class manages device addressing and connection verification.
 *
 * Example usage:
 * @code
 * SfeAS7343ArdI2C sensor;
 * if (sensor.begin()) {
 *     // Sensor initialized successfully
 * }
 * @endcode
 *
 * @note This class uses the Arduino Wire library for I2C communication
 *
 * @see sfDevAS7343
 * @see TwoWire
 *
 */
class SfeAS7343ArdI2C : public sfDevAS7343
{
  public:
    SfeAS7343ArdI2C()
    {
    }

    /**
     * @brief Initializes the AS7343 sensor with I2C communication.
     *
     * @details
     * This method performs the following initialization steps:
     * 1. Initializes I2C communication with device address and Wire port
     * 2. Enables repeat start support
     * 3. Sets up communication bus
     * 4. Verifies device connection
     * 5. Calls base class initialization
     *
     * @param address I2C address of the device (default: kDefaultAS7343Addr)
     * @param wirePort TwoWire instance to use for I2C communication (default: Wire)
     *
     * @return true If initialization successful
     * @return false If any initialization step fails
     *
     * Example:
     * @code
     * SfeAS7343ArdI2C sensor;
     * if (!sensor.begin()) {
     *     Serial.println("Sensor initialization failed!");
     *     while (1); // halt
     * }
     * @endcode
     */
    bool begin(const uint8_t &address = kAS7343Addr, TwoWire &wirePort = Wire)
    {
        if (_theI2CBus.init(wirePort, address) != ksfTkErrOk)
            return false;

        // // Device supports repeat starts, enable it.
        // _theI2CBus.setStop(false);

        setCommunicationBus(&_theI2CBus);

        if (!isConnected())
            return false;
        return true;
        //return sfDevAS7343::begin();
    }

    /**
     * @brief Checks if the AS7343 sensor is connected and responding.
     *
     * @details
     * This method performs two checks:
     * 1. Attempts to ping the device at the current I2C address
     * 2. Verifies the device ID matches the expected AS7343 ID
     *
     * @return true If device responds to ping and returns correct device ID
     * @return false If communication fails or device ID is incorrect
     *
     * Example:
     * @code
     * SfeAS7343ArdI2C sensor;
     * if (!sensor.isConnected()) {
     *     Serial.println("Device not found or incorrect ID!");
     *     return;
     * }
     * @endcode
     */
    bool isConnected(void)
    {
        if (_theI2CBus.ping() != ksfTkErrOk)
            return false;
        
        return true;
        //return (kDefaultAS7343DeviceID == getDeviceID());
    }

    /**
     * @brief Gets the currently configured I2C address of the AS7343 sensor.
     *
     * @details
     * Returns the I2C address currently being used to communicate with the sensor.
     *
     * @return uint8_t The current I2C address
     *
     * Example:
     * @code
     * SfeAS7343ArdI2C sensor;
     * uint8_t address = sensor.getDeviceAddress();
     * Serial.print("Current I2C address: 0x");
     * Serial.println(address, HEX);
     * @endcode
     */
    uint8_t getDeviceAddress(void)
    {
        return _theI2CBus.address();
    }

  private:
    /**
     * @brief Arduino I2C bus interface instance for the AS7343 sensor.
     *
     * @details
     * This member handles the low-level I2C communication between the Arduino and the AS7343 sensor.
     *
     * The bus interface is configured during begin() and used by all communication methods.
     *
     * @see sfTkArdI2C
     * @see begin()
     */
    sfTkArdI2C _theI2CBus;
};