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
} sfe_as7343_reg_bank_t;

// Sensor Channels
// Use these to access each channel individually from the _data array in the class.
// The channels are defined in the datasheet as FZ, FY, FXL, NIR, 2xVIS, FD, F1-F8.
// When AutoSmux is set to 18 channels, the channels are in this order:
// Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
// Cycle 2: F2, F3, F4, F6, 2xVIS, FD
// Cycle 3: F1, F7, F8, F5, 2xVIS, FD
typedef enum
{
    CH_BLUE_FZ_450NM = 0x00, // Blue peak wavelength 450 nanometers (cycle 1)
    CH_GREEN_FY_555NM, // Green (wide bandwidth) peak wavelength 555 nanometers (cycle 1)
    CH_ORANGE_FXL_600NM, // Orange peak wavelength 600 nanometers (cycle 1)
    CH_NIR_855NM, // NIR peak wavelength 855 nanometers (cycle 1)
    CH_VIS_1, // VIS (cycle 1)
    CH_FD_1, // Flicker Detection (cycle 1)
    CH_DARK_BLUE_F2_425NM, // Dark Blue peak wavelength 425 nanometers (cycle 2)
    CH_LIGHT_BLUE_F3_475NM, // Light Blue peak wavelength 475 nanometers (cycle 2)
    CH_BLUE_F4_515NM, // Blue peak wavelength 515 nanometers (cycle 2)
    CH_BROWN_F6_640NM, // Brown peak wavelength 640 nanometers (cycle 2)
    CH_VIS_2, // VIS (cycle 2)
    CH_FD_2, // Flicker Detection (cycle 2)
    CH_PURPLE_F1_405NM, // Purple peak wavelength 405 nanometers (cycle 3)
    CH_RED_F7_690NM, // Red peak wavelength 690 nanometers (cycle 3)
    CH_DARK_RED_F8_745NM, // Dark Red peak wavelength 745 nanometers (cycle 3)
    CH_GREEN_F5_550NM, // Green (Narrow bandwidth) peak wavelength 550 nanometers (cycle 3)
    CH_VIS_3, // VIS (cycle 3)
    CH_FD_3, // Flicker Detection (cycle 3)
} sfe_as7343_channel_t;

// Sensor number of channels constant, used to determine the number of bytes
// read from the device when using the readSpectraDataFromSensor() function, and also
// to determine the size of the _data array in the class.
const uint8_t ksfAS7343NumChannels = 18; // Number of channels in the AS7343 sensor

// Sensor gain settings.
typedef enum
{
    AGAIN_0_5 = 0x00, // 0.5x gain
    AGAIN_1,
    AGAIN_2,
    AGAIN_4,
    AGAIN_8,
    AGAIN_16,
    AGAIN_32,
    AGAIN_64,
    AGAIN_128,
    AGAIN_256,
    AGAIN_512,
    AGAIN_1024,
    AGAIN_2048,

} sfe_as7343_again_t;

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
} sfe_as7343_fd_gain_t;

// FIFO Threshold settings
// Sets a threshold on the FIFO level that triggers the first FIFO buffer 
// interrupt (FINT).
typedef enum
{
    FIFO_THRESHOLD_LVL_1 = 0x00,
    FIFO_THRESHOLD_LVL_4,
    FIFO_THRESHOLD_LVL_8,
    FIFO_THRESHOLD_LVL_16,
} sfe_as7343_fifo_threshold_t;

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
} sfe_as7343_spectral_threshold_channel_t;

// Automatic Channel Read-out (auto_smux setting)
typedef enum
{
    AUTOSMUX_6_CHANNELS = 0x00, // 6 channel readout: FZ, FY, FXL, NIR, 2xVIS, FD
    AUTOSMUX_12_CHANNELS = 0x02, // 12 channel readout
                           // Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
                            // Cycle 2: FZ, F3, F4, F6, 2xVIS, FD
    AUTOSMUX_18_CHANNELS = 0x03, // 18 channel readout
                            // Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
                            // Cycle 2: F2, F3, F4, F6, 2xVIS, FD
                            // Cycle 3: F1, F7, F8, F5, 2xVIS, FD 
} sfe_as7343_auto_smux_channel_t;

// GPIO mode settings
typedef enum
{
    AS7343_GPIO_MODE_OUTPUT = 0x00, // GPIO set to output mode
    AS7343_GPIO_MODE_INPUT, // GPIO set to input mode
} sfe_as7343_gpio_mode_t;

// GPIO output settings
typedef enum
{
    AS7343_GPIO_OUTPUT_LOW = 0x00, // GPIO set to low
    AS7343_GPIO_OUTPUT_HIGH, // GPIO set to high
} sfe_as7343_gpio_output_t;

///////////////////////////////////////////////////////////////////////////////
// Register Definitions
///////////////////////////////////////////////////////////////////////////////

const uint8_t ksfAS7343RegAuxID = 0x58; // Register Address

// A union is used here so that individual values from the register can be
// accessed or the whole register can be accessed.
typedef union {
    struct
    {
        uint8_t auxid : 4;
        uint8_t reserved : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_auxid_t;

const uint8_t ksfAS7343RegRevID = 0x59; // Register Address

typedef union {
    struct
    {
        uint8_t revid : 3;
        uint8_t reserved : 5;
    };
    uint8_t byte;
} sfe_as7343_reg_revid_t;

const uint8_t ksfAS7343RegID = 0x5A; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_id_t;

const uint8_t ksfAS7343RegCfg12 = 0x66; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t sp_th_ch : 3;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg12_t;

const uint8_t ksfAS7343RegEnable = 0x80; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_enable_t;

const uint8_t ksfAS7343RegATime = 0x81; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_atime_t;

const uint8_t ksfAS7343RegWTime = 0x83; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_wtime_t;

const uint8_t ksfAS7343RegSpThL = 0x84; // Register Address

typedef union {
    struct
    {
        uint8_t sp_th_l_lsb : 8;
        uint8_t sp_th_l_msb : 8;
    };
    uint16_t word;
} sfe_as7343_reg_sp_th_l_t;


const uint8_t ksfAS7343RegSpThH = 0x86; // Register Address

typedef union {
    struct
    {
        uint8_t sp_th_h_lsb : 8;
        uint8_t sp_th_h_msb : 8;
    };
    uint16_t word;
} sfe_as7343_reg_sp_th_h_t;

const uint8_t ksfAS7343RegStatus = 0x93; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_status_t;

const uint8_t ksfAS7343RegAStatus = 0x94; // Register Address

typedef union {
    struct
    {
        uint8_t again_status : 4;
        uint8_t reserved : 3;
        uint8_t asat_satatus : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_astatus_t;

const uint8_t ksfAS7343RegData0 = 0x95; // Register Address
const uint8_t ksfAS7343RegData1 = 0x97; // Register Address
const uint8_t ksfAS7343RegData2 = 0x99; // Register Address
const uint8_t ksfAS7343RegData3 = 0x9B; // Register Address
const uint8_t ksfAS7343RegData4 = 0x9D; // Register Address
const uint8_t ksfAS7343RegData5 = 0x9F; // Register Address
const uint8_t ksfAS7343RegData6 = 0xA1; // Register Address
const uint8_t ksfAS7343RegData7 = 0xA3; // Register Address
const uint8_t ksfAS7343RegData8 = 0xA5; // Register Address
const uint8_t ksfAS7343RegData9 = 0xA7; // Register Address
const uint8_t ksfAS7343RegData10 = 0xA9; // Register Address
const uint8_t ksfAS7343RegData11 = 0xAB; // Register Address
const uint8_t ksfAS7343RegData12 = 0xAD; // Register Address
const uint8_t ksfAS7343RegData13 = 0xAF; // Register Address
const uint8_t ksfAS7343RegData14 = 0xB1; // Register Address
const uint8_t ksfAS7343RegData15 = 0xB3; // Register Address
const uint8_t ksfAS7343RegData16 = 0xB5; // Register Address
const uint8_t ksfAS7343RegData17 = 0xB7; // Register Address

typedef union {
    struct
    {
        uint8_t data_l : 8;
        uint8_t data_h : 8;
    };
    uint16_t word;
} sfe_as7343_reg_data_t;

const uint8_t ksfAS7343RegStatus2 = 0x90; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_status2_t;

const uint8_t ksfAS7343RegStatus3 = 0x91; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t int_sp_l : 1;
        uint8_t int_sp_h : 1;
        uint8_t reserved_one : 2;
    };
    uint8_t byte;
} sfe_as7343_reg_status3_t;

const uint8_t ksfAS7343RegStatus4 = 0xBC; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_status4_t;

const uint8_t ksfAS7343RegFdStatus = 0xE3; // Register Address

typedef union {
    struct
    {
        uint8_t fd_100hz_det : 1;
        uint8_t fd_120hz_det : 1;
        uint8_t fd_100hz_valid : 1;
        uint8_t fd_120hz_valid : 1;
        uint8_t fd_saturation : 1;
        uint8_t fd_meas_valid : 1;
        uint8_t reserved : 2;
    };
    uint8_t byte;
} sfe_as7343_reg_fd_status_t;

const uint8_t ksfAS7343RegStatus5 = 0x93; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 2;
        uint8_t sint_smux : 1;
        uint8_t sint_fd : 1;
        uint8_t reserved_one : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_data_status5_t;

const uint8_t ksfAS7343RegCfg0 = 0xBF; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_cfg0_t;

const uint8_t ksfAS7343RegCfg1 = 0xC6; // Register Address

typedef union {
    struct
    {
        uint8_t again : 5;
        uint8_t reserved: 3;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg1_t;

const uint8_t ksfAS7343RegCfg3 = 0xC7; // Register Address

typedef union {
    struct
    {
        uint8_t reserved: 4;
        uint8_t sai : 1;
        uint8_t reserved2: 3;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg3_t;

const uint8_t ksfAS7343RegCfg6 = 0xF5; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 3;
        uint8_t smux_cmd: 2;
        uint8_t reserved_one : 3;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg6_t;

const uint8_t ksfAS7343RegCfg8 = 0xC9; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 6;
        uint8_t fifo_th: 2;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg8_t;

const uint8_t ksfAS7343RegCfg9 = 0xCA; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t sienc_smux: 1;
        uint8_t reserved_one : 1;
        uint8_t sienc_fd: 1;
        uint8_t reserved_two : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg9_t;

const uint8_t ksfAS7343RegCfg10 = 0x65; // Register Address

typedef union {
    struct
    {
        uint8_t fd_pers : 3;
        uint8_t reserved : 5;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg10_t;

const uint8_t ksfAS7343RegPers = 0xCF; // Register Address

typedef union {
    struct
    {
        uint8_t apers : 4;
        uint8_t reserved : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_pers_t;

const uint8_t ksfAS7343RegGpio = 0x6B; // Register Address

typedef union {
    struct
    {
        uint8_t gpio_in : 1;
        uint8_t gpio_out : 1;
        uint8_t gpio_in_en : 1;
        uint8_t gpio_inv : 1;
        uint8_t reserved : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_gpio_t;

const uint8_t ksfAS7343RegAStep = 0xD4; // Register Address

typedef union {
    struct
    {
        uint8_t astep_l : 8;
        uint8_t astep_h : 8;
    };
    uint16_t word;
} sfe_as7343_reg_astep_t;

const uint8_t ksfAS7343RegCfg20 = 0xD6; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t auto_smux : 2;
        uint8_t fd_fifo_8b : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_cfg20_t;

const uint8_t ksfAS7343RegLed = 0xCD; // Register Address

typedef union {
    struct
    {
        uint8_t led_drive : 7;
        uint8_t led_act : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_led_t;

const uint8_t ksfAS7343RegAgcGainMax = 0xD7; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t agc_fd_gain_max : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_agc_gain_max_t;

const uint8_t ksfAS7343RegAzConfig = 0xDE; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_az_config_t;

const uint8_t ksfAS7343RegFdTime1 = 0xE0; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_fd_time_1_t;

const uint8_t ksfAS7343RegFdTime2 = 0xE2; // Register Address

typedef union {
    struct
    {
        uint8_t fd_time_h : 3; // TODO: Unkown big order
        uint8_t fd_gain : 5;
    };
    uint8_t byte;
} sfe_as7343_reg_fd_time_2_t;

const uint8_t ksfAS7343RegFdTimeCfg0 = 0xDF; // Register Address

typedef union {
    struct
    {
        uint8_t reserved : 7;
        uint8_t fifo_write_fd : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_fd_cfg0_t;

const uint8_t ksfAS7343RegIntEnab = 0xF9; // Register Address

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
    uint8_t byte;
} sfe_as7343_reg_intenab_t;

const uint8_t ksfAS7343RegControl = 0xFA; // Register Address

typedef union {
    struct
    {
        uint8_t clear_sai_act : 1;
        uint8_t fifo_clr : 1;
        uint8_t sp_man_az : 1;
        uint8_t sw_reset : 1;
        uint8_t reserved : 4;
    };
    uint8_t byte;
} sfe_as7343_reg_control_t;

const uint8_t ksfAS7343RegFifoMap = 0xFC; // Register Address

typedef union {
    struct
    {
        uint8_t fifo_write_astatus : 1;
        uint8_t fifo_write_ch0_data : 1;
        uint8_t fifo_write_ch1_data : 1;
        uint8_t fifo_write_ch2_data : 1;
        uint8_t fifo_write_ch3_data : 1;
        uint8_t fifo_write_ch4_data : 1;
        uint8_t fifo_write_ch5_data : 1;
        uint8_t reserved : 1;
    };
    uint8_t byte;
} sfe_as7343_reg_fifo_map_t;

const uint8_t ksfAS7343RegFifoLvl = 0xFD; // Register Address, register is a single uint8_t.
typedef uint8_t sfe_as7343_reg_fifo_lvl_t;

const uint8_t ksfAS7343RegFData = 0xFE; // Register Address

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
    bool setRegisterBank(sfe_as7343_reg_bank_t regBank);

    /// @brief Power on or off the device.
    /// @details This method powers on or off the device by setting or clearing
    /// the PON bit in the Enable register (ksfAS7343RegEnable).
    /// @param power True to power on the device, false to power off.
    /// @return True if successful, false if it fails.
    bool powerOn(bool power = true);

    /// @brief Power off the device.
    /// @details This method powers off the device by clearing the PON bit in the
    /// Enable register (ksfAS7343RegEnable).
    /// @return True if successful, false if it fails.
    bool powerOff(void);

    /// @brief Enable or Disable the Spectral Measurement.
    /// @details This method enables or disables the spectral measurement by
    /// setting or clearing the SP_EN bit in the Enable register
    /// (ksfAS7343RegEnable).
    /// @param enable True to enable the spectral measurement, false to disable.
    /// @return True if successful, false if it fails.
    bool enableSpectralMeasurement(bool enable = true);

    /// @brief Spectral Measurement Disable
    /// @details This method disables the spectral measurement by calling the
    /// enableSpectralMeasurement method with false.
    /// @return True if successful, false if it fails.
    bool disableSpectralMeasurement(void);

    /// @brief Read all Spectral Data Registers
    /// @details This method reads all the spectral data registers from the
    /// AS7343 device. The data is stored in this drivers private struct variables.
    /// @details The data is stored in the _data array in the class. You can
    /// access the data using the getData() method, which returns the data from
    /// the specified channel. Another option is to use the getRed(), getGreen(),
    /// getBlue(), and getNIR() methods to get only those channels.
    /// @return True if successful, false if it fails.
    bool readSpectraDataFromSensor(void);

    /// @brief Get the data from the specified channel.
    /// @details You must call the readSpectraDataFromSensor() method before calling this
    /// method to get the most recent data from the specified channel.
    /// @param channel The channel to get the data from.
    /// @details Options: There are 17 total channels:
    /// CH_BLUE_FZ_450NM, CH_GREEN_FY_555NM, CH_ORANGE_FXL_600NM,
    /// CH_NIR_855NM, CH_VIS_1, CH_FD_1, CH_DARK_BLUE_F2_425NM, CH_LIGHT_BLUE_F3_475NM,
    /// CH_BLUE_F4_515NM, CH_BROWN_F6_640NM, CH_VIS_2, CH_FD_2, CH_PURPLE_F1_405NM,
    /// CH_RED_F7_690NM, CH_DARK_RED_F8_745NM, CH_GREEN_F5_550NM, CH_VIS_3, CH_FD_3.
    /// @see readSpectraDataFromSensor()
    /// @return The most recently read data from the specified channel.
    uint16_t getData(sfe_as7343_channel_t channel);

    /// @brief Set automatic channel read-out.
    /// @details This method sets the automatic channel read-out mode. The
    /// auto_smux setting in the CFG20 register (0xD6) can be set to 6, 12, or 18
    /// channels. The default is 6 channels.
    /// @param auto_smux The automatic channel read-out setting.
    /// @details Options: AUTOSMUX_6_CH (default), AUTOSMUX_12_CH,
    /// AUTOSMUX_18_CHANNELS.
    /// @return True if successful, false if it fails.
    bool setAutoSmux(sfe_as7343_auto_smux_channel_t auto_smux);

    /// @brief Turn on or off the LED.
    /// @details This method turns on or off the LED by setting or clearing the
    /// LED_ACT bit in the LED register (ksfAS7343RegLed).
    /// @param ledOn True to turn on the LED, false to turn off.
    /// @return True if successful, false if it fails.
    bool ledOn(bool ledOn = true);

    /// @brief Turn off the LED.
    /// @details This method turns off the LED by calling the ledOn method
    /// with false.
    /// @return True if successful, false if it fails.
    bool ledOff(void);

    /// @brief Set the LED drive current.
    /// @details This method sets the LED drive current by writing to the LED
    /// register (ksfAS7343RegLed). The LED drive current is set by writing to
    /// the LED_DRIVE bits in the LED register.
    /// @param ledDrive The LED drive current to set.
    /// @details Options: 0-127. (4-258mA)
    /// The drive current can be set to values of 0-127 (0-258 mA).
    /// 0 = 4mA, 1 = 6mA, 2 = 8mA, ...  127 = 258mA.
    /// default is 12mA.
    /// @return True if successful, false if it fails.
    bool setLedDrive(uint8_t ledDrive);

    /// @brief Get Red spectrum data. (aka channel F7, 690nm)
    /// @return The red spectrum data.
    uint16_t getRed(void);

    /// @brief Get Green spectrum data. (aka channel F5, 550nm)
    /// @return The green spectrum data.
    uint16_t getGreen(void);

    /// @brief Get Blue spectrum data. (aka channel FZ, 450nm)
    /// @return The blue spectrum data.
    uint16_t getBlue(void);

    /// @brief Get NIR spectrum data. (aka channel NIR, 855nm)
    /// @return The NIR spectrum data.  
    uint16_t getNIR(void);

    /// @brief Get Specific Channel of Spectrum Data
    /// @param channel The channel to get the data from. (uint8_t)
    /// @details Options: 0-17
    /// @return The data from the specified channel. Returns 0 on error or if the
    /// channel is invalid.
    uint16_t getChannelData(uint8_t channel);

    /// @brief Set the spectral interrupt threshold high.
    /// @details This method sets the spectral threshold high by writing to the
    /// SP_TH_H register (ksfAS7343RegSpThH). The spectral threshold high is set
    /// by writing to the SP_TH_H_LSB Register and SP_TH_H_MSB Register.
    /// @param spThH The spectral threshold high to set.
    /// @return True if successful, false if it fails.
    bool setSpectralIntThresholdHigh(uint16_t spThH);

    /// @brief Set the spectral interrupt threshold low.
    /// @details This method sets the spectral threshold low by writing to the
    /// SP_TH_L register (ksfAS7343RegSpThL). The spectral threshold low is set
    /// by writing to the SP_TH_L_LSB Register and SP_TH_L_MSB Register.
    /// @param spThL The spectral threshold low to set.
    /// @return True if successful, false if it fails.
    bool setSpectralIntThresholdLow(uint16_t spThL);

    /// @brief Enable or Disable the spectral interrupt.
    /// @details This method enables or disables the spectral interrupt by
    /// setting or clearing the SP_IEN bit in the INT_ENAB register
    /// (ksfAS7343RegIntEnab).
    /// @param enable True to enable the spectral interrupt, false to disable.
    /// @return True if successful, false if it fails.
    bool enableSpectralInterrupt(bool enable =  true);

    /// @brief Disable the spectral interrupt.
    /// @details This method disables the spectral interrupt by calling the
    /// enableSpectralInterrupt method with false.
    /// @return True if successful, false if it fails.
    bool disableSpectralInterrupt(void);

    /// @brief Set the spectral threshold channel.
    /// @details This method sets the spectral threshold channel by writing to
    /// the SP_TH_CH bits [2:0] in the CFG12 register, ksfAS7343RegCfg12 (0x66).
    /// @param spThCh The spectral threshold channel to set.
    /// @details Options: SPECTRAL_THRESHOLD_CHANNEL_0 (default),
    /// SPECTRAL_THRESHOLD_CHANNEL_1, SPECTRAL_THRESHOLD_CHANNEL_2,
    /// SPECTRAL_THRESHOLD_CHANNEL_3, SPECTRAL_THRESHOLD_CHANNEL_4, 
    /// SPECTRAL_THRESHOLD_CHANNEL_5.
    /// @return True if successful, false if it fails.
    bool setSpectralThresholdChannel(sfe_as7343_spectral_threshold_channel_t spThCh);

    /// @brief Get the System Interrupt Status.
    /// @details This method gets the system interrupt status by reading the
    /// SINT bit in the STATUS register (ksfAS7343RegStatus).
    /// @return True if the system interrupt is set, false if it is not set.
    bool getSystemInterruptStatus(void);

    /// @brief Get the Spectral Channel Interrupt Status.
    /// @details This method gets the spectral channel interrupt status by reading
    /// the AINT bit in the STATUS register (ksfAS7343RegStatus).
    /// @return True if the spectral channel interrupt is set, false if it is not set.
    bool getSpectralChannelInterruptStatus(void);

    /// @brief Clear Spectral Channel Interrupt bit (AINT).
    /// @details This method clears the spectral channel interrupt bit by writing
    /// a 1 to the AINT bit in the STATUS register (ksfAS7343RegStatus).
    /// @return True if successful, false if it fails.
    bool clearSpectralChannelInterrupt(void);

    /// @brief Get the Spectral Interrupt High Status.
    /// @details This method gets the spectral interrupt high status by reading
    /// the INT_PS_H bit in the STATUS3 register (ksfAS7343RegStatus3).
    /// @return True if the spectral interrupt high is set, false if it is not set.
    bool getSpectralInterruptHighStatus(void);

    /// @brief Get the Spectral Trigger Error Status.
    /// @details This method gets the spectral trigger error status by reading
    /// the SP_TRIG bit in the STATUS4 register (ksfAS7343RegStatus4).
    /// @return True if the spectral trigger error is set, false if it is not set.
    bool getSpectralTriggerErrorStatus(void);

    /// @brief Set the Spectral Measurement Wait Time.
    /// @details This method sets the spectral measurement wait time by writing
    /// to the WTIME register (ksfAS7343RegWTime).
    /// @param wTime The spectral measurement wait time to set.
    /// @details 8-bit value to specify the delay between two
    /// consecutive spectral measurements.
    /// The value is in units of 2.78ms. The default value is 0x00.
    /// @return True if successful, false if it fails.
    bool setWaitTime(uint8_t wTime);

    /// @brief Get the Spectral Measurement Wait Time.
    /// @details This method gets the spectral measurement wait time by reading
    /// the WTIME register (ksfAS7343RegWTime).
    /// @return The spectral measurement wait time.
    /// @details The value is in units of 2.78ms.
    /// The default value is 0x00.
    uint8_t getWaitTime(void);

    /// @brief Enable or Disable Wait Time.
    /// @details This method enables or disables the wait time by setting or
    /// clearing the WEN bit in the Enable register (ksfAS7343RegEnable).
    /// @param enable True to enable the wait time, false to disable.
    /// @return True if successful, false if it fails.
    bool enableWaitTime(bool enable = true);

    /// @brief Disable Wait Time.
    /// @details This method disables the wait time by calling the
    /// enableWaitTime method with false.
    /// @return True if successful, false if it fails.
    bool disableWaitTime(void);

    /// @brief Get the Spectral Valid Status.
    /// @details This method gets the spectral valid status by reading the AVALID
    /// bit in the STATUS2 register (ksfAS7343RegStatus2).
    /// @return True if the spectral valid status is set, false if it is not set.
    bool getSpectralValidStatus(void);

    /// @brief Read the register INT Enable
    /// @details This method reads the INT Enable register (ksfAS7343RegIntEnab).
    /// @return The INT Enable register value.
    /// @details The INT Enable register is a bit field that enables or disables
    /// the spectral interrupt, FIFO interrupt, and AGC interrupt.
    /// @return The INT Enable register value.
    uint8_t readIntEnableReg(void);

    /// @brief Set the GPIO pin mode.
    /// @details This method sets the GPIO pin mode by writing to the GPIO_IN_EN 
    /// and GPIO_OUT bits in the GPIO register (ksfAS7343RegGpio).
    /// @param gpioMode The GPIO pin mode to set.
    /// @details Options: AS7343_GPIO_MODE_INPUT (default), AS7343_GPIO_MODE_OUTPUT.
    /// @return True if successful, false if it fails.
    bool setGPIOMode(sfe_as7343_gpio_mode_t gpioMode);

    /// @brief Get the GPIO input status.
    /// @details This method gets the GPIO input status by reading the GPIO_IN bit
    /// in the GPIO register (ksfAS7343RegGpio).
    /// @return True if the GPIO input is reading HIGH, false if it is reading LOW.
    bool getGPIOInputStatus(void);

    /// @brief Set the GPIO output
    /// @details This method sets the GPIO output by writing to the GPIO_OUT bit
    /// in the GPIO register (ksfAS7343RegGpio).
    /// @param gpioOut The GPIO output to set.
    /// @details Options: AS7343_GPIO_OUTPUT_LOW (default), AS7343_GPIO_OUTPUT_HIGH.
    /// @return True if successful, false if it fails.
    bool setGPIOOutput(sfe_as7343_gpio_output_t gpioOut);

    /// @brief Reset the device.
    /// @details This method resets the device by writing to the SW_RESET bit in
    /// the CONTROL register (ksfAS7343RegControl).
    /// @return True if successful, false if it fails.
    bool reset(void);

    /// @brief Set the Spectral Interrupt Persistence
    /// @details This method sets the spectral interrupt persistence by writing to
    /// the PERS bits in the PERS register (ksfAS7343RegPers).
    /// @param apers The spectral interrupt persistence to set.
    /// @details Options:
    /// 0 = Every spectral cycle generates an interrupt.
    /// 1 = 1
    /// 2 = 2
    /// 3 = 3
    /// 4 = 5
    /// 5 = 10
    /// ... 5*(APERS - 3)
    /// 14 = 55
    /// 15 = 60
    /// @details The default value is 0x00.
    /// @return True if successful, false if it fails.
    bool setSpectralIntPersistence(uint8_t apers);

    /// @brief Read a register from the device.
    /// @details This method reads a register from the device
    /// @param reg The register to read.
    /// @param data Pointer to the register data to read into.
    /// @return True if successful, false if it fails.
    bool readRegisterBank(uint8_t reg, uint8_t &data);

    /// Brief Set AGAIN value
    /// @details This method sets the AGAIN value by writing to the AGAIN bits in
    /// the CFG1 register (ksfAS7343RegCfg1).
    /// @param again The AGAIN value to set.
    /// @details Options:
    /// AGAIN_0_5X (default), AGAIN_1X, AGAIN_2X, AGAIN_4X, AGAIN_8X, AGAIN_16X,
    /// AGAIN_32X, AGAIN_64X.
    /// @return True if successful, false if it fails.
    bool setAgain(sfe_as7343_again_t again);

    /// @brief Enable or Disable the Flicker Detection
    /// @details This method enables or disables the flicker detection by setting
    /// or clearing the FD_EN bit in the ENABLE register (ksfAS7343RegEnable).
    /// @param enable True to enable the flicker detection, false to disable.
    /// @return True if successful, false if it fails.
    bool flickerDetectionEnableDisable(bool enable);

    /// @brief Enable Flicker Detection
    /// @details This method enables flicker detection by calling the
    /// flickerDetectionEnableDisable method with true.
    /// @return True if successful, false if it fails.
    bool enableFlickerDetection(void);

    /// @brief Disable Flicker Detection
    /// @details This method disables flicker detection by calling the
    /// flickerDetectionEnableDisable method with false.
    /// @return True if successful, false if it fails.
    bool disableFlickerDetection(void);

    /// @brief Get the Flicker Detection Measurement Valid Status
    /// @details This method gets the flicker detection measurement valid status by
    /// reading the FD_MEAS_VALID bit in the FD_STATUS register
    /// (ksfAS7343RegFdStatus).
    /// @return True if the flicker detection measurement is valid, false if it is not valid.
    bool isFlickerDetectionValid(void);

    /// @brief Get the Flicker Detection Saturation Detected Status
    /// @details This method gets the flicker detection saturation detected status by
    /// reading the FD_SATURATION bit in the FD_STATUS register
    /// (ksfAS7343RegFdStatus).
    /// @return True if the flicker detection saturation is detected, false if it is not detected.
    bool isFlickerDetectionSaturated(void);

    /// @brief Get the Flicker Detection Frequency Detected
    /// @details This method gets the flicker detection frequency detected by reading
    /// the FD_100HZ_DET and FD_120HZ_DET bits in the FD_STATUS register
    /// (ksfAS7343RegFdStatus).
    /// @return The flicker detection frequency detected (100 or 120) 
    /// or 0 if no frequency is detected.
    uint8_t getFlickerDetectionFrequency(void);

  private:
    sfe_as7343_reg_data_t _data[ksfAS7343NumChannels]; // Array of data structs, to hold data from the sensor.

    sfTkIBus *_theBus; // Pointer to bus device.
};
