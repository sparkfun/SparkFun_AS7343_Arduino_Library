/**
 * @file sfDevAS7343.h
 * @brief Header file for the SparkFun Spectral Sensor - AS7343.
 *
 * This file contains the class definitions, constants, and enums for interacting with the AS7343 sensor.
 *
 * @details
 * SfeAS7343Driver is a comms-agnostic driver for the AS7343 Spectral sensor that uses the SparkFun Toolkit.
 * The SfeAS7343ArdI2C class defines the Arduino specific behavior for initializing and interacting with devices.
 *
 * @section Enums Enum Definitions
 * - Sensor gain settings
 * - Flicker Detection Gain Settings
 * - FIFO Threshold settings
 * - Spectral Threshold Channel
 * - Automatic Channel Read-out (auto_smux setting)
 *
 * @author SparkFun Electronics
 * @date 2025
 * @copyright Copyright (c) 2025, SparkFun Electronics Inc. This project is released under the MIT License.
 *
 * SPDX-License-Identifier: MIT
 *
 * @section Registers Configuration Register Descriptions
 * - Configuration Registers
 * - Measurement Registers
 *
 * @section Classes Classes
 * - sfDevAS7343
 *
 * @section Repository Repository
 * https://github.com/sparkfun/SparkFun_AS7343_Arduino_Library
 *
 * @section Product_Links Product Links
 * - Qwiic 1x1: https://www.sparkfun.com/products/23220
 *
 */

#pragma once

#include <stdint.h>

// include the sparkfun toolkit headers
#include <sfTk/sfToolkit.h>

// Bus interfaces
#include <sfTk/sfTkII2C.h>
///////////////////////////////////////////////////////////////////////////////
// I2C Addressing
///////////////////////////////////////////////////////////////////////////////
const uint8_t kAS7343Addr = 0x39; // I2C address for the AS7343 device.

const uint8_t kDefaultAS7343DeviceID = 0x81;  // When polling the ID register, this should be returned on boot.

///////////////////////////////////////////////////////////////////////////////
// Enum Definitions
///////////////////////////////////////////////////////////////////////////////

// Sensor Register Bank settings
typedef enum
{
    REG_BANK_0 = 0x00, // Register bank 0 (default)
    REG_BANK_1 = 0x01, // Register bank 1
} as7343_reg_bank_t;

// Sensor gain settings.
typedef enum
{
    GAIN_0_5 = 0x00, // 0.5x gain
    GAIN_1,
    GAIN_2,
    GAIN_4,
    GAIN_8,
    GAIN_16,
    GAIN_32,
    GAIN_64,
    GAIN_128,
    GAIN_256,
    GAIN_512,
    GAIN_1024,
    GAIN_2048,

} as7343_gain_t;

// Flicker Detection Gain Settings (ADC5)
typedef enum
{
    FD_GAIN_0_5 = 0x00, // 0.5x gain
    FD_GAIN_1,
    FD_GAIN_2,
    FD_GAIN_4,
    FD_GAIN_8,
    FD_GAIN_16,
    FD_GAIN_32,
    FD_GAIN_64,
    FD_GAIN_128,
    FD_GAIN_256,
    FD_GAIN_512,
    FD_GAIN_1024,
    FD_GAIN_2048,
} as7343_fd_gain_t;

// FIFO Threshold settings
// Sets a threshold on the FIFO level that triggers the first FIFO buffer 
// interrupt (FINT).
typedef enum
{
    FIFO_THRESHOLD_LVL_1 = 0x00,
    FIFO_THRESHOLD_LVL_4,
    FIFO_THRESHOLD_LVL_8,
    FIFO_THRESHOLD_LVL_16,
} as7343_fifo_threshold_t;

// Spectral Threshold Channel
// Sets the channel used for interrupts and persistence, if enabled, to 
// determine device status and gain settings.
typedef enum
{
    SPECTRAL_THRESHOLD_CHANNEL_0 = 0x00,
    SPECTRAL_THRESHOLD_CHANNEL_1,
    SPECTRAL_THRESHOLD_CHANNEL_2,
    SPECTRAL_THRESHOLD_CHANNEL_3,
    SPECTRAL_THRESHOLD_CHANNEL_4,
    SPECTRAL_THRESHOLD_CHANNEL_5,
} as7343_spectral_threshold_channel_t;

// Automatic Channel Read-out (auto_smux setting)
typedef enum
{
    AUTOSMUX_6_CH = 0x00, // 6 channel readout: FZ, FY, FXL, NIR, 2xVIS, FD
    AUTOSMUX_12_CH = 0x02, // 12 channel readout
                           // Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
                            // Cycle 2: FZ, F3, F4, F6, 2xVIS, FD
    AUTOSMUX_18_CHANNELS = 0x03, // 18 channel readout
                            // Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
                            // Cycle 2: F2, F3, F4, F6, 2xVIS, FD
                            // Cycle 3: F1, F7, F8, F5, 2xVIS, FD 
} as7343_auto_smux_channel_t;

///////////////////////////////////////////////////////////////////////////////
// Register Definitions
///////////////////////////////////////////////////////////////////////////////

const uint8_t kSfeAS7343RegAuxID = 0x58; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t auxid : 4;
        uint8_t reserved : 4;
    };
    uint8_t word;
} sfe_as7343_reg_auxid_t;

const uint8_t kSfeAS7343RegRevID = 0x59; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t revid : 3;
        uint8_t reserved : 5;
    };
    uint8_t word;
} sfe_as7343_reg_revid_t;

const uint8_t kSfeAS7343RegID = 0x5A; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_id_t;

const uint8_t kSfeAS7343RegCfg12 = 0x66; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t sp_th_ch : 3;
    };
    uint8_t word;
} sfe_as7343_reg_cfg12_t;

const uint8_t kSfeAS7343RegEnable = 0x80; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t pon : 1;
        uint8_t sp_en : 1;
        uint8_t reserved : 1;
        uint8_t wen : 1;
        uint8_t smuxen : 1;
        uint8_t reserved_one : 1;
        uint8_t fden : 1;
        uint8_t reserved_two : 1;
        uint8_t enable : 1;
    };
    uint8_t word;
} sfe_as7343_reg_enable_t;

const uint8_t kSfeAS7343RegATime = 0x81; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_atime_t;

const uint8_t kSfeAS7343RegWTime = 0x83; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_wtime_t;

const uint8_t kSfeAS7343RegSpThL = 0x84; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t sp_th_l_lsb : 8;
        uint8_t sp_th_l_msb : 8;
    };
    uint16_t word;
} sfe_as7343_reg_sp_th_l_t;


const uint8_t kSfeAS7343RegSpThH = 0x86; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t sp_th_h_lsb : 8;
        uint8_t sp_th_h_msb : 8;
    };
    uint16_t word;
} sfe_as7343_reg_sp_th_h_t;

const uint8_t kSfeAS7343RegStatus = 0x93; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t sint : 1;
        uint8_t reserved : 1;
        uint8_t fint : 1;
        uint8_t aint : 1;
        uint8_t reserved_one : 3;
        uint8_t asat : 1;
    };
    uint8_t word;
} sfe_as7343_reg_status_t;

const uint8_t kSfeAS7343RegAStatus = 0x94; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t again_status : 4;
        uint8_t reserved : 3;
        uint8_t asat_satatus : 1;
    };
    uint8_t word;
} sfe_as7343_reg_astatus_t;

// typedef for data registers
// Note, we are using the same typedef here for all data from the sensor.
// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t data_l : 8;
        uint8_t data_h : 8;
    };
    uint16_t word;
} sfe_as7343_reg_data_t;

const uint8_t kSfeAS7343RegData0 = 0x95; // Register Address
const uint8_t kSfeAS7343RegData1 = 0x97; // Register Address
const uint8_t kSfeAS7343RegData2 = 0x99; // Register Address
const uint8_t kSfeAS7343RegData3 = 0x9B; // Register Address
const uint8_t kSfeAS7343RegData4 = 0x9D; // Register Address
const uint8_t kSfeAS7343RegData5 = 0x9F; // Register Address
const uint8_t kSfeAS7343RegData6 = 0xA1; // Register Address
const uint8_t kSfeAS7343RegData7 = 0xA3; // Register Address
const uint8_t kSfeAS7343RegData8 = 0xA5; // Register Address
const uint8_t kSfeAS7343RegData9 = 0xA7; // Register Address
const uint8_t kSfeAS7343RegData10 = 0xA9; // Register Address
const uint8_t kSfeAS7343RegData11 = 0xAB; // Register Address
const uint8_t kSfeAS7343RegData12 = 0xAD; // Register Address
const uint8_t kSfeAS7343RegData13 = 0xAF; // Register Address
const uint8_t kSfeAS7343RegData14 = 0xB1; // Register Address
const uint8_t kSfeAS7343RegData15 = 0xB3; // Register Address
const uint8_t kSfeAS7343RegData16 = 0xB5; // Register Address
const uint8_t kSfeAS7343RegData17 = 0xB7; // Register Address

const uint8_t kSfeAS7343RegStatus2 = 0x90; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t fdsat_dig : 1;
        uint8_t fdsat_ana : 1;
        uint8_t reserved : 1;
        uint8_t asat_ana : 1;
        uint8_t asat_dig : 1;
        uint8_t reserved_one : 1;
        uint8_t avalid : 1;
        uint8_t reserved_two : 1;
    };
    uint8_t word;
} sfe_as7343_reg_status2_t;

const uint8_t kSfeAS7343RegStatus3 = 0x91; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t int_sp_l : 1;
        uint8_t int_sp_h : 1;
        uint8_t reserved_one : 2;
    };
    uint8_t word;
} sfe_as7343_reg_status3_t;

const uint8_t kSfeAS7343RegStatus4 = 0xBC; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t int_busy : 1;
        uint8_t sai_act : 1;
        uint8_t sp_trig : 1;
        uint8_t reserved : 1;
        uint8_t fd_trig : 1;
        uint8_t ov_temp : 1;
        uint8_t reserved_one : 1;
        uint8_t fifo_ov : 1;
    };
    uint8_t word;
} sfe_as7343_reg_status4_t;

const uint8_t kSfeAS7343RegStatus5 = 0x93; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 2;
        uint8_t sint_smux : 1;
        uint8_t sint_fd : 1;
        uint8_t reserved_one : 4;
    };
    uint8_t word;
} sfe_as7343_reg_data_status5_t;

const uint8_t kSfeAS7343RegCfg0 = 0xBF; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 2;
        uint8_t wlong : 1;
        uint8_t reserved_one : 1;
        uint8_t reg_bank : 1;
        uint8_t low_power : 1;
        uint8_t reserved_two : 2;
    };
    uint8_t word;
} sfe_as7343_reg_cfg0_t;

const uint8_t kSfeAS7343RegCfg1 = 0xC6; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t again : 5;
        uint8_t reserved: 3;
    };
    uint8_t word;
} sfe_as7343_reg_cfg1_t;

const uint8_t kSfeAS7343RegCfg3 = 0xC7; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved: 4;
        uint8_t again : 1;
        uint8_t reserved2: 3;
    };
    uint8_t word;
} sfe_as7343_reg_cfg3_t;

const uint8_t kSfeAS7343RegCfg6 = 0xF5; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 3;
        uint8_t smux_cmd: 2;
        uint8_t reserved_one : 3;
    };
    uint8_t word;
} sfe_as7343_reg_cfg6_t;

const uint8_t kSfeAS7343RegCfg8 = 0xC9; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 6;
        uint8_t fifo_th: 2;
    };
    uint8_t word;
} sfe_as7343_reg_cfg8_t;

const uint8_t kSfeAS7343RegCfg9 = 0xCA; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t sienc_smux: 1;
        uint8_t reserved_one : 1;
        uint8_t sienc_fd: 1;
        uint8_t reserved_two : 1;
    };
    uint8_t word;
} sfe_as7343_reg_cfg9_t;

const uint8_t kSfeAS7343RegCfg10 = 0x65; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t fd_pers : 3;
        uint8_t reserved : 5;
    };
    uint8_t word;
} sfe_as7343_reg_cfg10_t;

const uint8_t kSfeAS7343RegPers = 0xCF; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t PERS : 4;
        uint8_t reserved : 4;
    };
    uint8_t word;
} sfe_as7343_reg_pers_t;

const uint8_t kSfeAS7343RegGpio = 0x6B; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t gpio_in : 1;
        uint8_t gpio_out : 1;
        uint8_t gpio_in_en : 1;
        uint8_t gpio_inv : 1;
        uint8_t reserved : 4;
    };
    uint8_t word;
} sfe_as7343_reg_gpio_t;

const uint8_t kSfeAS7343RegAStep = 0xD4; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t astep_l : 8;
        uint8_t astep_h : 8;
    };
    uint16_t word;
} sfe_as7343_reg_astep_t;

const uint8_t kSfeAS7343RegCfg20 = 0xD6; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t auto_smux : 2;
        uint8_t fd_fifo_8b : 1;
    };
    uint8_t word;
} sfe_as7343_reg_cfg20_t;

const uint8_t kSfeAS7343RegLed = 0xCD; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t led_drive : 7;
        uint8_t led_act : 1;
    };
    uint8_t word;
} sfe_as7343_reg_led_t;

const uint8_t kSfeAS7343RegAgcGainMax = 0xD7; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t agc_fd_gain_max : 4;
    };
    uint8_t word;
} sfe_as7343_reg_agc_gain_max_t;

const uint8_t kSfeAS7343RegAzConfig = 0xDE; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_az_config_t;

const uint8_t kSfeAS7343RegFdTime1 = 0xE0; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_fd_time_1_t;

const uint8_t kSfeAS7343RegFdTime2 = 0xE2; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t fd_time_h : 3; // TODO: Unkown big order
        uint8_t fd_gain : 5;
    };
    uint8_t word;
} sfe_as7343_reg_fd_time_2_t;

const uint8_t kSfeAS7343RegFdTimeCfg0 = 0xDF; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t reserved : 7;
        uint8_t fifo_write_fd : 1;
    };
    uint8_t word;
} sfe_as7343_reg_fd_cfg0_t;

const uint8_t kSfeAS7343RegFdStatus = 0xE3; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t fd_100Hz : 1;
        uint8_t fd_120Hz : 1;
        uint8_t fd_100Hz_valid : 1;
        uint8_t fd_120Hz_valid : 1;
        uint8_t fd_sat : 1;
        uint8_t fd_valid : 1;
        uint8_t fd_reserved : 2;
    };
    uint8_t word;
} sfe_as7343_reg_fd_status_t;

const uint8_t kSfeAS7343RegIntEnab = 0xF9; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t sein : 1;
        uint8_t reserved : 1;
        uint8_t fien : 1;
        uint8_t sp_ien : 1;
        uint8_t reserved_one : 3;
        uint8_t asien : 1;
    };
    uint8_t word;
} sfe_as7343_reg_intenab_t;

const uint8_t kSfeAS7343RegControl = 0xFA; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t clear_sai_act : 1;
        uint8_t fifo_clr : 1;
        uint8_t sp_man_az : 1;
        uint8_t sw_reset : 1;
        uint8_t reserved : 4;
    };
    uint8_t word;
} sfe_as7343_reg_control_t;

const uint8_t kSfeAS7343RegFifoMap = 0xFC; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t astatus : 1;
        uint8_t fifo_write_ch5_data_fifo_write_ch0_data : 6;
        uint8_t reserved : 6;
    };
    uint8_t word;
} sfe_as7343_reg_fifo_map_t;

const uint8_t kSfeAS7343RegFifoLvl = 0xFD; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_fifo_lvl_t;

const uint8_t kSfeAS7343RegFData = 0xFE; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t fdata_l : 8;
        uint8_t fdata_h : 8;
    };
    uint16_t word;
} sfe_as7343_reg_fifo_data_t;


///////////////////////////////////////////////////////////////////////////////

class sfDevAS7343
{
  public:
    sfDevAS7343()
    {
    }

    /// @brief This method is called to initialize the AS7343 device through the
    /// specified bus.
    /// @param theBus Pointer to the bus object.
    /// @return True if successful, false if it fails.
    bool begin(sfTkIBus *theBus = nullptr);

    /// @brief Requests the device ID from the sensor.
    /// @return The device ID of the sensor.
    uint8_t getDeviceID(void);

    /// @brief Sets the communication bus to the specified bus.
    /// @param theBus Bus to set as the communication device.
    void setCommunicationBus(sfTkIBus *theBus);

    /// @brief Set the register bank.
    /// In order to access registers from 0x58 to 0x66, bit REG_BANK in register 
    /// CFG0 (0xBF) needs to be set to “1”. For register access of registers 
    /// 0x80 and above bit REG_BANK needs to be set to “0”
    /// @param regBank The register bank to set. 
    /// @details Options: REG_BANK_0 (default), REG_BANK_1.
    /// @return True if successful, false if it fails.
    bool setRegisterBank(as7343_reg_bank_t regBank);

    /// @brief Power on the device.
    /// @details This method powers on the device by setting the PON bit in the
    /// Enable register (kSfeAS7343RegEnable).
    /// @return True if successful, false if it fails.
    bool powerOn(void);

    /// @brief Power off the device.
    /// @details This method powers off the device by clearing the PON bit in the
    /// Enable register (kSfeAS7343RegEnable).
    /// @return True if successful, false if it fails.
    bool powerOff(void);

    /// @brief Spectral Measurement Enable
    /// @details This method enables the spectral measurement by setting the
    /// SP_EN bit in the Enable register (kSfeAS7343RegEnable).
    /// @return True if successful, false if it fails.
    bool spectralMeasurementEnable(void);

    /// @brief Spectral Measurement Disable
    /// @details This method disables the spectral measurement by clearing the
    /// SP_EN bit in the Enable register (kSfeAS7343RegEnable).
    /// @return True if successful, false if it fails.
    bool spectralMeasurementDisable(void);

    /// @brief Read all Spectral Data Registers
    /// @details This method reads all the spectral data registers from the
    /// AS7343 device. The data is stored in this drivers private struct variables.
    /// @return True if successful, false if it fails.
    bool readAllSpectralData(void);

    /// @brief Get the data from the specified channel.
    /// @param channel The channel to get the data from.
    /// @return The data from the specified channel.
    uint16_t getData(uint8_t channel);

    /// @brief Set automatic channel read-out.
    /// @details This method sets the automatic channel read-out mode. The
    /// auto_smux setting in the CFG20 register (0xD6) can be set to 6, 12, or 18
    /// channels. The default is 6 channels.
    /// @param auto_smux The automatic channel read-out setting.
    /// @details Options: AUTOSMUX_6_CH (default), AUTOSMUX_12_CH,
    /// AUTOSMUX_18_CHANNELS.
    /// @return True if successful, false if it fails.
    bool setAutoSmux(as7343_auto_smux_channel_t auto_smux);

    /// @brief Turn on the LED.
    /// @details This method turns on the LED by setting the LED_ACT bit in the
    /// LED register (kSfeAS7343RegLed).
    /// @return True if successful, false if it fails.
    bool ledOn(void);

    /// @brief Turn off the LED.
    /// @details This method turns off the LED by clearing the LED_ACT bit in the
    /// LED register (kSfeAS7343RegLed).
    /// @return True if successful, false if it fails.
    bool ledOff(void);

    /// @brief Set the LED drive current.
    /// @details This method sets the LED drive current by writing to the LED
    /// register (kSfeAS7343RegLed). The LED drive current is set by writing to
    /// the LED_DRIVE bits in the LED register.
    /// @param ledDrive The LED drive current to set.
    /// @details Options: 0-127. (4-258mA)
    /// The drive current can be set to values of 0-127 (0-258 mA).
    /// 0 = 4mA, 1 = 6mA, 2 = 8mA, ...  127 = 258mA.
    /// default is 12mA.
    /// @return True if successful, false if it fails.
    bool setLedDrive(uint8_t ledDrive);


  private:
    sfe_as7343_reg_data_t _data[18]; // Array of data structs, to hold data from the sensor.

    sfTkIBus *_theBus; // Pointer to bus device.
};
