/**
 * @file sfDevAS7343.cpp
 * @brief Implementation file for the SparkFun AS7343 Sensor device driver.
 *
 * @details
 * This file implements the sfDevAS7343 class methods for configuring and reading data from
 * the AS7343 sensor. The driver provides a comms-agnostic interface using the SparkFun Toolkit.
 *
 * Key features:
 * - Device initialization and configuration
 * - Sensor readings
 * - Gain settings
 * - Power management
 *
 * @section Implementation Implementation Details
 * - Register read/write operations
 *
 * @author SparkFun Electronics
 * @date 2025
 * @copyright Copyright (c) 2024-2025, SparkFun Electronics Inc. All rights reserved.
 *
 * @section License License
 * SPDX-License-Identifier: MIT
 *
 * @see https://github.com/sparkfun/SparkFun_AS7343_Arduino_Library
 */
#include "sfDevAS7343.h"

bool sfDevAS7343::begin(sfTkIBus *theBus)
{
    // Nullptr check.
    if (!_theBus && !theBus)
        return false;

    // Set the internal bus pointer, overriding current bus if it exists.
    if (theBus != nullptr)
        setCommunicationBus(theBus);

    // Get the device setup and ready.
    //return runDefaultSetup();
}

uint8_t sfDevAS7343::getDeviceID(void)
{
    // Nullptr check.
    if (!_theBus)
        return 0;

    // Set the register bank to 1, needed to read the device ID register (0x5A)
    // If it fails, return 0.

    if (setRegisterBank(REG_BANK_1) == false)
        return 0;

    uint8_t devID; // Create a variable to hold the device ID.

    // Read the device ID register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegID, devID))
        return 0;

    return devID;
}

void sfDevAS7343::setCommunicationBus(sfTkIBus *theBus)
{
    _theBus = theBus;
}

bool sfDevAS7343::setRegisterBank(as7343_reg_bank_t regBank)
{
    // Nullptr check.
    if (!_theBus)
        return 0;

    sfe_as7343_reg_cfg0_t cfg0; // Create a register structure for CFG0

    // Read the cfg0 register (to retain other bits), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegCfg0, cfg0.word))
        return 0;

    // set the reg_bank bit as set by the incoming argument
    if(regBank == REG_BANK_1)
        cfg0.reg_bank = 1;
    else
        cfg0.reg_bank = 0;

    // Write the cfg0 register to the device. If it errors, then return 0.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegCfg0, cfg0.word))
        return 0;

    return true; // Return true to indicate success
}

bool sfDevAS7343::powerOn(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 1, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_1) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegID, enableReg.word))
    return false;

    // Set the PON bit to 1 to power on the device
    enableReg.pon = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    return true;
}

bool sfDevAS7343::powerOff(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 1, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_1) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegID, enableReg.word))
        return false;

    // Set the PON bit to 0 to power off the device
    enableReg.pon = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    return true;
}

bool sfDevAS7343::spectralMeasurementEnable(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 1, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_1) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    // Set the SP_EN bit to 1 to enable spectral measurement
    enableReg.sp_en = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    return true;
}

bool sfDevAS7343::spectralMeasurementDisable(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 1, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_1) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    // Set the SP_EN bit to 0 to disable spectral measurement
    enableReg.sp_en = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.word))
        return false;

    return true;
}

bool sfDevAS7343::readAllSpectralData(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the data registers (0x80 and above).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    size_t nRead = 0; // Create a variable to hold the number of bytes read.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegData0, (uint8_t*)_data, 36, nRead))
        return false;

    // Check if the number of bytes read is correct.
    if (nRead != 36)
        return false;

    return true;
}

uint16_t sfDevAS7343::getData(uint8_t channel)
{
    // Check if the channel is valid (0-17).
    if (channel > 17)
        return 0;

    // Return the data for the specified channel.
    return _data[channel].word;
}