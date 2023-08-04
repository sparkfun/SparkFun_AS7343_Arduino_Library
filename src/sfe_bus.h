// sfe_bus.cpp
//
// This is a library written for SparkFun Tristimulus Color Sensors OPT4048
//
// SparkFun sells these bpards at its website: www.sparkfun.com
//
// Do you like this library? Help support SparkFun. Buy a board!
//
//----------------PRODUCTS HERE--------------------
//
// Written by Elias Santistevan @ SparkFun Electronics,
//
// Repository:
//	    * https://github.com/Sparkfun/SparkFun_AS7343_Arduino_Library
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
// and Serial Peripheral Interface (SPI). For ease of implementation
// an abstract interface (QwIDeviceBus) is used.

#pragma once

#include <Wire.h>

namespace sfe_AS7343
{

/// @brief This is an abstract interface for the I2C bus.
class QwDeviceBus
{
  public:
    virtual bool ping(uint8_t address) = 0;

    virtual int writeRegisterRegion(uint8_t address, uint8_t offset, uint8_t *data, uint16_t length) = 0;

    virtual int readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes) = 0;
};

/// @brief This class implements the I2C interface for the OPT4048
class QwI2C : public QwDeviceBus
{
  public:
    QwI2C(void);

    bool init();

    bool init(TwoWire &wirePort, bool bInit = false);

    bool ping(uint8_t address);

    int writeRegisterRegion(uint8_t address, uint8_t offset, uint8_t *data, uint16_t length);

    int readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes);

  private:
    TwoWire *_i2cPort;
};

} // namespace sfe_AS7343
