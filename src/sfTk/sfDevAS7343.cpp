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
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegCfg0, cfg0.byte))
        return 0;

    // set the reg_bank bit as set by the incoming argument
    if(regBank == REG_BANK_1)
        cfg0.reg_bank = 1;
    else
        cfg0.reg_bank = 0;

    // Write the cfg0 register to the device. If it errors, then return 0.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegCfg0, cfg0.byte))
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
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegID, enableReg.byte))
    return false;

    // Set the PON bit to 1 to power on the device
    enableReg.pon = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
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
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegID, enableReg.byte))
        return false;

    // Set the PON bit to 0 to power off the device
    enableReg.pon = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
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
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the SP_EN bit to 1 to enable spectral measurement
    enableReg.sp_en = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
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
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the SP_EN bit to 0 to disable spectral measurement
    enableReg.sp_en = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
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

uint16_t sfDevAS7343::getData(as7343_channel_t channel)
{
    // Check if the channel is valid (0-17).
    if (channel > 17)
        return 0;

    // Return the data for the specified channel.
    return _data[channel].word;
}

bool sfDevAS7343::setAutoSmux(as7343_auto_smux_channel_t auto_smux)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the CFG20 register (0xD6).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_cfg20_t cfg20; // Create a register structure for the CFG20 register

    // Read the CFG20 register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegCfg20, cfg20.byte))
        return false;

    // Set the auto_smux bits according to the incoming argument
    cfg20.auto_smux = auto_smux;

    // Write the CFG20 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegCfg20, cfg20.byte))
        return false;

    return true;
}

bool sfDevAS7343::ledOn(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the LED register (0xCD).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_led_t ledReg; // Create a register structure for the LED register

    // Read the LED register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    // Set the LED_ACT bit to 1 to turn on the LED
    ledReg.led_act = 1;

    // Write the LED register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::ledOff(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the LED register (0xCD).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_led_t ledReg; // Create a register structure for the LED register

    // Read the LED register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    // Set the LED_ACT bit to 0 to turn off the LED
    ledReg.led_act = 0;

    // Write the LED register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    return true;
}


bool sfDevAS7343::setLedDrive(uint8_t drive)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Check if the drive current is within the valid range (0-127).
    if (drive > 127)
        return false;

    // Set the register bank to 0, needed to access the LED register (0xCD).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_led_t ledReg; // Create a register structure for the LED register

    // Read the LED register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    // Set the LED drive current according to the incoming argument
    ledReg.led_drive = drive;

    // Write the LED register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegLed, ledReg.byte))
        return false;

    return true;
}

uint16_t sfDevAS7343::getRed(void)
{
    // Return the data for the red channel (F7).
    return getData(CH_RED_F7_690NM);
}

uint16_t sfDevAS7343::getGreen(void)
{
    // Return the data for the green channel (F5).
    return getData(CH_GREEN_F5_550NM);
}

uint16_t sfDevAS7343::getBlue(void)
{
    // Return the data for the blue channel (FZ).
    return getData(CH_BLUE_FZ_450NM);
}

uint16_t sfDevAS7343::getNIR(void)
{
    // Return the data for the NIR channel (NIR).
    return getData(CH_NIR_855NM);
}

uint16_t sfDevAS7343::getChannelData(uint8_t channel)
{
    // Check if the channel is valid (0-17).
    if (channel > 17)
        return 0;

    // Return the data for the specified channel.
    return getData((as7343_channel_t)channel);
}

bool sfDevAS7343::setSpectralIntThresholdHigh(uint16_t spThH)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the SP_TH_H register (0xD8).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    // Write both LSB and MSB in the same I2C write. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegSpThH, (uint8_t*)&spThH, 2))
        return false;

    return true;
}

bool sfDevAS7343::setSpectralIntThresholdLow(uint16_t spThL)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the SP_TH_L register (0xD9).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    // Write both LSB and MSB in the same I2C write. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegSpThL, (uint8_t*)&spThL, 2))
        return false;

    return true;
}

bool sfDevAS7343::enableSpectralInt()
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the SP_TH_L register (0xD9).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_intenab_t intEnabReg; // Create a register structure for the INT_ENAB register

    // Read the INT_ENAB register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegIntEnab, intEnabReg.byte))
        return false;
    
    // Set the SP_IEN bit to 1 to enable the spectral interrupt
    intEnabReg.sp_ien = 1;

    // Write the INT_ENAB register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegIntEnab, intEnabReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableSpectralInt()
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the SP_TH_L register (0xD9).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_intenab_t intEnabReg; // Create a register structure for the INT_ENAB register

    // Read the INT_ENAB register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegIntEnab, intEnabReg.byte))
        return false;
    
    // Set the SP_IEN bit to 0 to disable the spectral interrupt
    intEnabReg.sp_ien = 0;

    // Write the INT_ENAB register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegIntEnab, intEnabReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::setSpectralThresholdChannel(as7343_spectral_threshold_channel_t spThCh)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 1, needed to access the CFG12 register (0x66).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_1) == false)
        return false;

    sfe_as7343_reg_cfg12_t cfg12; // Create a register structure for the CFG12 register

    // Read the CFG12 register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegCfg12, cfg12.byte))
        return false;

    // Set the SP_TH_CH bits according to the incoming argument
    cfg12.sp_th_ch = spThCh;

    // Write the CFG12 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegCfg12, cfg12.byte))
        return false;

    return true;
}

bool sfDevAS7343::getSystemInterruptStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS register (0x93).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus, statusReg.byte))
        return false;

    // Return the SINT bit from the STATUS register
    return statusReg.sint;
}

bool sfDevAS7343::getSpectralChannelInterruptStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS register (0x93).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus, statusReg.byte))
        return false;

    // Return the AINT bit from the STATUS register
    return statusReg.aint;
}

bool sfDevAS7343::getSpectralInterruptHighStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS3 register (0x91).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status3_t statusReg; // Create a register structure for the STATUS3 register

    // Read the STATUS3 register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus3, statusReg.byte))
        return false;

    // Return the INT_SP_H bit from the STATUS3 register
    return statusReg.int_sp_h;
}

bool sfDevAS7343::getSpectralTriggerErrorStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS4 register (0xBC).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status4_t statusReg; // Create a register structure for the STATUS4 register

    // Read the STATUS4 register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus4, statusReg.byte))
        return false;

    // Return the SP_TRIG bit from the STATUS4 register
    return statusReg.sp_trig;
}

bool sfDevAS7343::setWaitTime(uint8_t waitTime)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the WTIME register (0x83).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    // Write the wait time to the WTIME register. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegWTime, waitTime))
        return false;

    return true;
}

uint8_t sfDevAS7343::getWaitTime()
{
    // Nullptr check.
    if (!_theBus)
        return 0;

    // Set the register bank to 0, needed to access the WTIME register (0x83).
    // If it fails, return 0.
    if (setRegisterBank(REG_BANK_0) == false)
        return 0;

    uint8_t waitTime; // Create a variable to hold the wait time.

    // Read the WTIME register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegWTime, waitTime))
        return 0;

    return waitTime;
}

bool sfDevAS7343::enableWaitTime(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the WEN bit to 1 to enable wait time
    enableReg.wen = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableWaitTime(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the Enable register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the WEN bit to 0 to disable wait time
    enableReg.wen = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::getSpectralValidStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS2 register (0x90).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status2_t statusReg; // Create a register structure for the STATUS2 register

    // Read the STATUS2 register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus2, statusReg.byte))
        return false;

    // Return the AVALID bit from the STATUS2 register
    return statusReg.avalid;
}

uint8_t sfDevAS7343::readIntEnableReg(void)
{
    // Nullptr check.
    if (!_theBus)
        return 0;

    // Set the register bank to 0, needed to access the INT_ENAB register (0xA0).
    // If it fails, return 0.
    if (setRegisterBank(REG_BANK_0) == false)
        return 0;

    uint8_t intEnabReg; // Create a variable to hold the INT_ENAB register value.

    // Read the INT_ENAB register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegIntEnab, intEnabReg))
        return 0;

    return intEnabReg;
}

bool sfDevAS7343::setGpioMode(as7343_gpio_mode_t gpioMode)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the GPIO register (0x6B).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegGpio, gpioReg.byte))
        return false;

    // Set the GPIO_IN_EN and GPIO_OUT bits according to the incoming argument
    // gpioMode = AS7343_GPIO_MODE_INPUT or AS7343_GPIO_MODE_OUTPUT
    if (gpioMode == AS7343_GPIO_MODE_INPUT)
    {
        gpioReg.gpio_in_en = 1; // Set GPIO_IN_EN bit to 1 for input mode
    }
    else if (gpioMode == AS7343_GPIO_MODE_OUTPUT)
    {
        gpioReg.gpio_in_en = 0; // Set GPIO_IN_EN bit to 0 for output mode
    }
    else
    {
        return false; // Invalid GPIO mode, return false
    }

    // Write the GPIO register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegGpio, gpioReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::getGpioInputStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the GPIO register (0xA1).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegGpio, gpioReg.byte))
        return false;

    // Return the GPIO_IN bit from the GPIO register
    return gpioReg.gpio_in;
}

bool sfDevAS7343::setGpioOutput(sfe_as7343_gpio_output_t gpioOut)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the GPIO register (0xA1).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegGpio, gpioReg.byte))
        return false;

    // Set the GPIO_OUT bit according to the incoming argument
    gpioReg.gpio_out = gpioOut;

    // Write the GPIO register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegGpio, gpioReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::reset(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the CONTROL register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_control_t controlReg; // Create a register structure for the CONTROL register

    // Read the CONTROL register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegControl, controlReg.byte))
        return false;

    // Set the SW_RESET bit to 1 to reset the device
    controlReg.sw_reset = 1;

    // Write the CONTROL register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegControl, controlReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::setSpectralIntPersistence(uint8_t apers)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the PERS register (0xA2).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_pers_t persReg; // Create a register structure for the PERS register

    // Read the PERS register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegPers, persReg.byte))
        return false;

    // Set the PERS bits according to the incoming argument
    persReg.apers = apers;

    // Write the PERS register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegPers, persReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::clearSpectralChannelInterrupt(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the STATUS register (0x93).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegStatus, statusReg.byte))
        return false;

    // Clear the AINT bit by writing a 1 to it
    statusReg.aint = 1;

    // Write the STATUS register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegStatus, statusReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::readRegister(uint8_t reg, uint8_t &data)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank as needed to access the specified register.
    // if the desired register is equal to or greater than 0x80, set bank 0.
    // Otherwise, set bank 1.
    if (reg >= 0x80)
    {
        if (setRegisterBank(REG_BANK_0) == false)
            return false;
    }
    else
    {
        if (setRegisterBank(REG_BANK_1) == false)
            return false;
    }

    // Read the specified register. If it errors, then return false.
    if (ksfTkErrOk != _theBus->readRegister(reg, data))
        return false;

    return true;
}

bool sfDevAS7343::setAgain(as7343_again_t again)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the CFG1 register (0xC6).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_cfg1_t cfg1; // Create a register structure for the CFG0 register

    // Read the CFG0 register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegCfg1, cfg1.byte))
        return false;

    // Set the AGC bits according to the incoming argument
    cfg1.again = again;

    // Write the CFG0 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegCfg1, cfg1.byte))
        return false;

    return true;
}

bool sfDevAS7343::enableFlickerDetection(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;
    
    // Set the register bank to 0, needed to access the ENABLE Register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the FLICKER_EN bit to 1 to enable flicker detection
    enableReg.fden = 1;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableFlickerDetection(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the ENABLE Register (0x80).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    // Set the FLICKER_EN bit to 0 to disable flicker detection
    enableReg.fden = 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(kSfeAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::getFdValidStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the FD_STATUS register (0xE3).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegFdStatus, fdStatusReg.byte))
        return false;   

    // Return the FD_VALID bit from the FD_STATUS register
    return fdStatusReg.fd_meas_valid;
}

// get flicker detection saturation status
bool sfDevAS7343::getFdSaturationStatus(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0, needed to access the FD_STATUS register (0xE3).
    // If it fails, return false.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegFdStatus, fdStatusReg.byte))
        return false;   

    // Return the FD_SAT bit from the FD_STATUS register
    return fdStatusReg.fd_saturation;
}

uint8_t sfDevAS7343::getFdFrequency(void)
{
    // Nullptr check.
    if (!_theBus)
        return 0;

    // Set the register bank to 0, needed to access the FD_STATUS register (0xE3).
    // If it fails, return 0.
    if (setRegisterBank(REG_BANK_0) == false)
        return 0;

    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(kSfeAS7343RegFdStatus, fdStatusReg.byte))
        return 0;

    // See which frequency bit is set (fd_100hz_det or fd_120hz_det) and check
    // its corresponding valid bit (fd_100hz_valid or fd_120hz_valid) to determine the frequency
    // return the frequency value
    if (fdStatusReg.fd_100hz_det && fdStatusReg.fd_100hz_valid)
        return 100;
    else if (fdStatusReg.fd_120hz_det && fdStatusReg.fd_120hz_valid)
        return 120;
    else
        return 0; // No valid frequency detected
}

