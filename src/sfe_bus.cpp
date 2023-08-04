// sfe_bus.cpp
//
// This is a library written for SparkFun Qwiic OPT4048 boards
//
// SparkFun sells these bpards at its website: www.sparkfun.com
//
// Do you like this library? Help support SparkFun. Buy a board!
//
// ----------------------Product Name Here-----------------------
//
// Written by Kirk Benell @ SparkFun Electronics
// Modified by Elias Santistevan @ SparkFun Electronics, April 2022
//
// Repository:
//     https://github.com/sparkfun/SparkFun_AS7343_Arduino_Library
//
//
// SparkFun code, firmware, and software is released under the MIT
// License(http://opensource.org/licenses/MIT).
//
// SPDX-License-Identifier: MIT
//
//    The MIT License (MIT)
//
//    Copyright (c) 2022 SparkFun Electronics
//    Permission is hereby granted, free of charge, to any person obtaining a
//    copy of this software and associated documentation files (the "Software"),
//    to deal in the Software without restriction, including without limitation
//    the rights to use, copy, modify, merge, publish, distribute, sublicense,
//    and/or sell copies of the Software, and to permit persons to whom the
//    Software is furnished to do so, subject to the following conditions: The
//    above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
//    "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//    NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//    PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
//    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// The following classes specify the behavior for communicating
// over the respective data buses: Inter-Integrated Circuit (I2C)

#include "sfe_bus.h"
#include <Arduino.h>

#define kMaxTransferBuffer 32

// What we use for transfer chunk size
const static uint16_t kChunkSize = kMaxTransferBuffer;

namespace sfe_AS7343
{

QwI2C::QwI2C(void) : _i2cPort{nullptr}
{
}

/// @brief  Initializes I2C and checks for device
/// @param wirePort I2C port
/// @param bInit   If true, initializes the I2C port
/// @return True if device is present and initialized, false otherwise
bool QwI2C::init(TwoWire &wirePort, bool bInit)
{

    // if we don't have a wire port already
    if (!_i2cPort)
    {
        _i2cPort = &wirePort;

        if (bInit)
            _i2cPort->begin();
    }

    return true;
}

/// @brief Initializes I2C and checks for device
/// @return True if device is present and initialized, false otherwise
bool QwI2C::init()
{
    if (!_i2cPort)
        return init(Wire);
    else
        return false;
}

/// @brief Checks for device presence on the I2C bus
/// @param i2c_address I2C address of device
/// @return True if device is present, false otherwise
bool QwI2C::ping(uint8_t i2c_address)
{

    if (!_i2cPort)
        return false;

    _i2cPort->beginTransmission(i2c_address);
    return _i2cPort->endTransmission() == 0;
}

/// @brief Reads a register region from a device.
/// @param i2c_address I2C address of device
/// @param offset Register offset to read from
/// @param data Pointer to byte to store read data
/// @param length Number of bytes to read
/// @return Number of bytes read (-1 indicates failure)
int QwI2C::writeRegisterRegion(uint8_t i2c_address, uint8_t offset, uint8_t *data, uint16_t length)
{

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(data, (int)length);

    return _i2cPort->endTransmission() ? -1 : 0; // -1 = error, 0 = success
}

/// @brief Reads a single byte from a register
/// @param addr I2C address of device
/// @param reg  Register offset to read from
/// @param data Pointer to byte to store read data
/// @param numBytes Number of bytes to read
/// @return Number of bytes read (-1 indicates failure)
int QwI2C::readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes)
{
    uint8_t nChunk;
    uint16_t nReturned;

    if (!_i2cPort)
        return -1;

    int i;
    bool bFirstInter = true;

    while (numBytes > 0)
    {
        _i2cPort->beginTransmission(addr);

        if (bFirstInter)
        {
            _i2cPort->write(reg);
            bFirstInter = false;
        }

        if (_i2cPort->endTransmission() != 0)
            return -1;

        // We're chunking in data - keeping the max chunk to kMaxI2CBufferLength
        nChunk = numBytes > kChunkSize ? kChunkSize : numBytes;

        nReturned = _i2cPort->requestFrom((int)addr, (int)nChunk, (int)true);

        if (nReturned == 0)
            return -1;

        for (i = 0; i < nReturned; i++)
        {
            *data++ = _i2cPort->read();
        }

        // Decrement the amount of data recieved from the overall data request amount
        numBytes = numBytes - nReturned;

    } // end while

    return 0; // Success
}

} // namespace sfe_AS7343
