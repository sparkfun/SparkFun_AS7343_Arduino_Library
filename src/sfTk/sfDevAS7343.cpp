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

const uint8_t ksfLEDMaxCurrentDrive = 127; // Maximum LED drive current

const uint8_t ksfRegisterBank0Limit = 0x80; // start of the bank 0 registers

bool sfDevAS7343::begin(sfTkIBus *theBus)
{
    // Nullptr check.
    if (!_theBus && !theBus)
        return false;

    // Set the internal bus pointer, overriding current bus if it exists.
    if (theBus != nullptr)
        setCommunicationBus(theBus);

    return true; // Return true to indicate success
}

uint8_t sfDevAS7343::getDeviceID(void)
{
    uint8_t devID; // Create a variable to hold the device ID.

    // Read the device ID register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegID, devID) == false)
        return 0;

    return devID;
}

void sfDevAS7343::setCommunicationBus(sfTkIBus *theBus)
{
    _theBus = theBus;
}

bool sfDevAS7343::setRegisterBank(sfe_as7343_reg_bank_t regBank)
{

    sfe_as7343_reg_cfg0_t cfg0; // Create a register structure for CFG0

    // Read the cfg0 register (to retain other bits), if it errors then return 0.
    if (ksfTkErrOk != _theBus->readRegister(ksfAS7343RegCfg0, cfg0.byte))
        return false;

    // set the reg_bank bit as set by the incoming argument
    if (regBank == REG_BANK_1)
        cfg0.reg_bank = 1;
    else
        cfg0.reg_bank = 0;

    // Write the cfg0 register to the device. If it errors, then return 0.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegCfg0, cfg0.byte))
        return false;

    return true; // Return true to indicate success
}

bool sfDevAS7343::powerOn(bool power)
{
    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register, if it errors then return false.
    if (readRegisterBank(ksfAS7343RegID, enableReg.byte) == false)
        return false;

    // Set the PON bit according to the incoming argument
    enableReg.pon = power ? 1 : 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::powerOff(void)
{
    return powerOn(false);
}

bool sfDevAS7343::enableSpectralMeasurement(bool enable)
{
    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the enable register (to retain other bit settings), if it errors then return false.
    if (readRegisterBank(ksfAS7343RegEnable, enableReg.byte) == false)
        return false;

    // Set the SP_EN bit according to the incoming argument
    enableReg.sp_en = enable ? 1 : 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableSpectralMeasurement(void)
{
    return enableSpectralMeasurement(false);
}

bool sfDevAS7343::readSpectraDataFromSensor(void)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank to 0 to access the data registers.
    if (setRegisterBank(REG_BANK_0) == false)
        return false;

    // Calculate the number of data bytes to read.
    uint8_t numOfDataBytes = ksfAS7343NumChannels * sizeof(sfe_as7343_reg_data_t);

    size_t nRead = 0; // Create a variable to hold the number of bytes read.

    if (ksfTkErrOk != _theBus->readRegister(ksfAS7343RegData0, (uint8_t *)_data, numOfDataBytes, nRead))
        return false;

    // Check if the number of bytes read is correct.
    if (nRead != numOfDataBytes)
        return false;

    return true;
}

uint16_t sfDevAS7343::getChannelData(sfe_as7343_channel_t channel)
{
    // Check if the channel is valid (0-17).
    if (channel >= ksfAS7343NumChannels)
        return 0;

    // Return the data for the specified channel.
    return _data[channel].word;
}

uint8_t sfDevAS7343::getData(uint16_t *data, size_t size)
{
    // Check if the data pointer is valid and the size is valid
    if (!data || size > ksfAS7343NumChannels)
        return 0;

    uint8_t nWritten = 0; // keep track of how many data bytes were written

    // Copy the data from the internal buffer to the provided array.
    for (size_t i = 0; i < size; i++)
        data[i] = _data[i].word;

    nWritten = size;

    return nWritten;
}

bool sfDevAS7343::setAutoSmux(sfe_as7343_auto_smux_channel_t auto_smux)
{
    sfe_as7343_reg_cfg20_t cfg20; // Create a register structure for the CFG20 register

    // Read the CFG20 register (to retain other bit settings), if it errors then return false.
    if (readRegisterBank(ksfAS7343RegCfg20, cfg20.byte) == false)
        return false;

    // Set the auto_smux bits according to the incoming argument
    cfg20.auto_smux = auto_smux;

    // Write the CFG20 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegCfg20, cfg20.byte))
        return false;

    return true;
}

bool sfDevAS7343::ledOn(bool ledOn)
{
    sfe_as7343_reg_led_t ledReg; // Create a register structure for the LED register

    // Read the LED register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegLed, ledReg.byte) == false)
        return false;

    // Set the LED_ACT bit according to the incoming argument
    ledReg.led_act = ledOn ? 1 : 0;

    // Write the LED register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegLed, ledReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::ledOff(void)
{
    return ledOn(false);
}

bool sfDevAS7343::setLedDrive(uint8_t drive)
{
    // Check if the drive current is within the valid range (0-ksfMaxCurrentDrive(127)).
    if (drive > ksfLEDMaxCurrentDrive)
        return false;

    sfe_as7343_reg_led_t ledReg; // Create a register structure for the LED register

    // Read the LED register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegLed, ledReg.byte) == false)
        return false;

    // Set the LED drive current according to the incoming argument
    ledReg.led_drive = drive;

    // Write the LED register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegLed, ledReg.byte))
        return false;

    return true;
}

uint16_t sfDevAS7343::getRed(void)
{
    // Return the data for the red channel (F7).
    return getChannelData(CH_RED_F7_690NM);
}

uint16_t sfDevAS7343::getGreen(void)
{
    // Return the data for the green channel (F5).
    return getChannelData(CH_GREEN_F5_550NM);
}

uint16_t sfDevAS7343::getBlue(void)
{
    // Return the data for the blue channel (FZ).
    return getChannelData(CH_BLUE_FZ_450NM);
}

uint16_t sfDevAS7343::getNIR(void)
{
    // Return the data for the NIR channel (NIR).
    return getChannelData(CH_NIR_855NM);
}

bool sfDevAS7343::setSpectralIntThresholdHigh(uint16_t spThH)
{
    // Write both LSB and MSB in the same I2C write. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegSpThH, (uint8_t *)&spThH, 2))
        return false;

    return true;
}

bool sfDevAS7343::setSpectralIntThresholdLow(uint16_t spThL)
{
    // Write both LSB and MSB in the same I2C write. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegSpThL, (uint8_t *)&spThL, 2))
        return false;

    return true;
}

bool sfDevAS7343::enableSpectralInterrupt(bool enable)
{
    sfe_as7343_reg_intenab_t intEnabReg; // Create a register structure for the INT_ENAB register

    // Read the INT_ENAB register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegIntEnab, intEnabReg.byte) == false)
        return false;

    // Set the SP_IEN bit according to the incoming argument
    intEnabReg.sp_ien = enable ? 1 : 0;

    // Write the INT_ENAB register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegIntEnab, intEnabReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableSpectralInterrupt()
{
    return enableSpectralInterrupt(false);
}

bool sfDevAS7343::setSpectralThresholdChannel(sfe_as7343_spectral_threshold_channel_t spThCh)
{
    sfe_as7343_reg_cfg12_t cfg12; // Create a register structure for the CFG12 register

    // Read the CFG12 register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegCfg12, cfg12.byte) == false)
        return false;

    // Set the SP_TH_CH bits according to the incoming argument
    cfg12.sp_th_ch = spThCh;

    // Write the CFG12 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegCfg12, cfg12.byte))
        return false;

    return true;
}

bool sfDevAS7343::getSystemInterruptStatus(void)
{
    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus, statusReg.byte) == false)
        return false;

    // Return the SINT bit from the STATUS register
    return statusReg.sint;
}

bool sfDevAS7343::getSpectralChannelInterruptStatus(void)
{
    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus, statusReg.byte) == false)
        return false;

    // Return the AINT bit from the STATUS register
    return statusReg.aint;
}

bool sfDevAS7343::getSpectralInterruptHighStatus(void)
{
    sfe_as7343_reg_status3_t statusReg; // Create a register structure for the STATUS3 register

    // Read the STATUS3 register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus3, statusReg.byte) == false)
        return false;

    // Return the INT_SP_H bit from the STATUS3 register
    return statusReg.int_sp_h;
}

bool sfDevAS7343::getSpectralTriggerErrorStatus(void)
{
    sfe_as7343_reg_status4_t statusReg; // Create a register structure for the STATUS4 register

    // Read the STATUS4 register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus4, statusReg.byte) == false)
        return false;

    // Return the SP_TRIG bit from the STATUS4 register
    return statusReg.sp_trig;
}

bool sfDevAS7343::setWaitTime(uint8_t waitTime)
{
    // Write the wait time to the WTIME register. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegWTime, waitTime))
        return false;

    return true;
}

uint8_t sfDevAS7343::getWaitTime()
{
    uint8_t waitTime; // Create a variable to hold the wait time.

    // Read the WTIME register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegWTime, waitTime) == false)
        return 0;

    return waitTime;
}

bool sfDevAS7343::enableWaitTime(bool enable)
{
    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegEnable, enableReg.byte) == false)
        return false;

    // Set the WEN bit according to the incoming argument
    enableReg.wen = enable ? 1 : 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableWaitTime(void)
{
    return enableWaitTime(false);
}

bool sfDevAS7343::getSpectralValidStatus(void)
{
    sfe_as7343_reg_status2_t statusReg; // Create a register structure for the STATUS2 register

    // Read the STATUS2 register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus2, statusReg.byte) == false)
        return false;

    // Return the AVALID bit from the STATUS2 register
    return statusReg.avalid;
}

uint8_t sfDevAS7343::readIntEnableReg(void)
{
    uint8_t intEnabReg; // Create a variable to hold the INT_ENAB register value.

    // Read the INT_ENAB register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegIntEnab, intEnabReg) == false)
        return 0;

    return intEnabReg;
}

bool sfDevAS7343::setGPIOMode(sfe_as7343_gpio_mode_t gpioMode)
{
    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegGpio, gpioReg.byte) == false)
        return false;

    // Check if the GPIO mode is valid (input or output).
    if (gpioMode != AS7343_GPIO_MODE_INPUT && gpioMode != AS7343_GPIO_MODE_OUTPUT)
        return false;

    // Set the GPIO_IN_EN bit according to the incoming argument
    gpioReg.gpio_in_en = (uint8_t)gpioMode;

    // Write the GPIO register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegGpio, gpioReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::getGPIOInputStatus(void)
{
    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegGpio, gpioReg.byte) == false)
        return false;

    // Return the GPIO_IN bit from the GPIO register
    return gpioReg.gpio_in;
}

bool sfDevAS7343::setGPIOOutput(sfe_as7343_gpio_output_t gpioOut)
{
    sfe_as7343_reg_gpio_t gpioReg; // Create a register structure for the GPIO register

    // Read the GPIO register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegGpio, gpioReg.byte) == false)
        return false;

    // Set the GPIO_OUT bit according to the incoming argument
    gpioReg.gpio_out = gpioOut;

    // Write the GPIO register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegGpio, gpioReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::reset(void)
{
    sfe_as7343_reg_control_t controlReg; // Create a register structure for the CONTROL register

    // Read the CONTROL register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegControl, controlReg.byte) == false)
        return false;

    // Set the SW_RESET bit to 1 to reset the device
    controlReg.sw_reset = 1;

    // Write the CONTROL register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegControl, controlReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::setSpectralIntPersistence(uint8_t apers)
{
    sfe_as7343_reg_pers_t persReg; // Create a register structure for the PERS register

    // Read the PERS register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegPers, persReg.byte) == false)
        return false;

    // Set the PERS bits according to the incoming argument
    persReg.apers = apers;

    // Write the PERS register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegPers, persReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::clearSpectralChannelInterrupt(void)
{
    sfe_as7343_reg_status_t statusReg; // Create a register structure for the STATUS register

    // Read the STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegStatus, statusReg.byte) == false)
        return false;

    // Clear the AINT bit by writing a 1 to it
    statusReg.aint = 1;

    // Write the STATUS register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegStatus, statusReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::readRegisterBank(uint8_t reg, uint8_t &data)
{
    // Nullptr check.
    if (!_theBus)
        return false;

    // Set the register bank as needed to access the specified register.
    // if the desired register is equal to or greater than ksfRegisterBank0Limit (0x80),
    // set bank 0. Otherwise, set bank 1.
    sfe_as7343_reg_bank_t regBank = reg >= ksfRegisterBank0Limit ? REG_BANK_0 : REG_BANK_1;

    if (setRegisterBank(regBank) == false)
        return false;

    // Read the specified register. If it errors, then return false.
    if (ksfTkErrOk != _theBus->readRegister(reg, data))
        return false;

    return true;
}

bool sfDevAS7343::setAgain(sfe_as7343_again_t again)
{
    sfe_as7343_reg_cfg1_t cfg1; // Create a register structure for the CFG0 register

    // Read the CFG0 register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegCfg1, cfg1.byte) == false)
        return false;

    // Set the AGC bits according to the incoming argument
    cfg1.again = again;

    // Write the CFG0 register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegCfg1, cfg1.byte))
        return false;

    return true;
}

bool sfDevAS7343::enableFlickerDetection(bool enable)
{
    sfe_as7343_reg_enable_t enableReg; // Create a register structure for the Enable register

    // Read the Enable register (to retain other bit settings), if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegEnable, enableReg.byte) == false)
        return false;

    // Set the FLICKER_EN bit according to the incoming argument
    enableReg.fden = enable ? 1 : 0;

    // Write the Enable register to the device. If it errors, then return false.
    if (ksfTkErrOk != _theBus->writeRegister(ksfAS7343RegEnable, enableReg.byte))
        return false;

    return true;
}

bool sfDevAS7343::disableFlickerDetection(void)
{
    return enableFlickerDetection(false);
}

bool sfDevAS7343::isFlickerDetectionValid(void)
{
    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegFdStatus, fdStatusReg.byte) == false)
        return false;

    // Return the FD_VALID bit from the FD_STATUS register
    return fdStatusReg.fd_meas_valid;
}

bool sfDevAS7343::isFlickerDetectionSaturated(void)
{
    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegFdStatus, fdStatusReg.byte) == false)
        return false;

    // Return the FD_SAT bit from the FD_STATUS register
    return fdStatusReg.fd_saturation;
}

uint8_t sfDevAS7343::getFlickerDetectionFrequency(void)
{
    sfe_as7343_reg_fd_status_t fdStatusReg; // Create a register structure for the FD_STATUS register

    // Read the FD_STATUS register, if it errors then return 0.
    if (readRegisterBank(ksfAS7343RegFdStatus, fdStatusReg.byte) == false)
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
