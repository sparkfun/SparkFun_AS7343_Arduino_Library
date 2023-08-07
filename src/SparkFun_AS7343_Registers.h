// LITTLE ENDIAN
//
#pragma once
#include <cstdint>
#include <stdint.h>

#define AS7343_ONLY_ADDR 0x39

#define SFE_AS7343_REGISTER_AUXID 0x58
typedef union {
    struct
    {
        uint8_t auxid : 4;
        uint8_t reserved : 4;
    };
    uint8_t word;
} as7343_auxid_reg_t;

#define SFE_AS7343_REGISTER_REV_ID 0x59
typedef union {
    struct
    {
        uint8_t revid : 3;
        uint8_t reserved : 5;
    };
    uint8_t word;
} as7343_revid_reg_t;

#define SFE_AS7343_REGISTER_ID 0x5A
typedef union {
    struct
    {
        uint8_t ID : 8;
    };
    uint8_t word;
} as7343_id_reg_t;

#define SFE_AS7343_REGISTER_CFG12 0x66
typedef union {
    struct
    {
        uint8_t sp_th_ch : 3;
    };
    uint8_t word;
} as7343_cfg12_reg_t;

#define SFE_AS7343_REGISTER_ENABLE 0x80
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
} as7343_enable_reg_t;

#define SFE_AS7343_REGISTER_ATIME 0x81
typedef union {
    struct
    {
        uint8_t atime : 8;
    };
    uint8_t word;
} as7343_atime_reg_t;


#define SFE_AS7343_REGISTER_WTIME 0x83
typedef union {
    struct
    {
        uint8_t wtime : 8;
    };
    uint8_t word;
} as7343_wtime_reg_t;

#define SFE_AS7343_REGISTER_SP_TH_L 0x84
typedef union {
    struct
    {
        uint8_t sp_th_l_lsb : 8;
        uint8_t sp_th_l_msb : 8;
    };
    uint16_t word;
} as7343_sp_th_l_reg_t;


#define SFE_AS7343_REGISTER_SP_TH_H 0x86
typedef union {
    struct
    {
        uint8_t sp_th_h_lsb : 8;
        uint8_t sp_th_h_msb : 8;
    };
    uint16_t word;
} as7343_sp_th_h_reg_t;

#define SFE_AS7343_REGISTER_STATUS 0x93
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
} as7343_status_reg_t;

#define SFE_AS7343_REGISTER_ASTATUS 0x94
typedef union {
    struct
    {
        uint8_t again_status : 4;
        uint8_t reserved : 3;
        uint8_t asat_satatus : 1;
    };
    uint8_t word;
} as7343_astatus_reg_t;

#define SFE_AS7343_REGISTER_DATA_0 0x95
typedef union {
    struct
    {
        uint8_t data_0_l : 8;
        uint8_t data_0_h : 8;
    };
    uint16_t word;
} as7343_data_0_reg_t;


#define SFE_AS7343_REGISTER_DATA_1 0x97
typedef union {
    struct
    {
        uint8_t data_1_l : 8;
        uint8_t data_1_h : 8;
    };
    uint16_t word;
} as7343_data_1_reg_t;

#define SFE_AS7343_REGISTER_DATA_2 0x99
typedef union {
    struct
    {
        uint8_t data_2_l : 8;
        uint8_t data_2_h : 8;
    };
    uint16_t word;
} as7343_data_2_reg_t;

#define SFE_AS7343_REGISTER_DATA_3 0x9B
typedef union {
    struct
    {
        uint8_t data_3_l : 8;
        uint8_t data_3_h : 8;
    };
    uint16_t word;
} as7343_data_3_reg_t;

#define SFE_AS7343_REGISTER_DATA_4 0x9D
typedef union {
    struct
    {
        uint8_t data_4_l : 8;
        uint8_t data_4_h : 8;
    };
    uint16_t word;
} as7343_data_4_reg_t;

#define SFE_AS7343_REGISTER_DATA_5 0x9F
typedef union {
    struct
    {
        uint8_t data_5_l : 8;
        uint8_t data_5_h : 8;
    };
    uint16_t word;
} as7343_data_5_reg_t;


#define SFE_AS7343_REGISTER_DATA_6 0xA1
typedef union {
    struct
    {
        uint8_t data_6_l : 8;
        uint8_t data_6_h : 8;
    };
    uint16_t word;
} as7343_data_6_reg_t;

#define SFE_AS7343_REGISTER_DATA_7 0xA3
typedef union {
    struct
    {
        uint8_t data_7_l : 8;
        uint8_t data_7_h : 8;
    };
    uint16_t word;
} as7343_data_7_reg_t;

#define SFE_AS7343_REGISTER_DATA_8 0xA5
typedef union {
    struct
    {
        uint8_t data_8_l : 8;
        uint8_t data_8_h : 8;
    };
    uint16_t word;
} as7343_data_8_reg_t;

#define SFE_AS7343_REGISTER_DATA_9 0xA7
typedef union {
    struct
    {
        uint8_t data_9_l : 8;
        uint8_t data_9_h : 8;
    };
    uint16_t word;
} as7343_data_9_reg_t;

#define SFE_AS7343_REGISTER_DATA_10 0xA9
typedef union {
    struct
    {
        uint8_t data_10_l : 8;
        uint8_t data_10_h : 8;
    };
    uint16_t word;
} as7343_data_10_reg_t;

#define SFE_AS7343_REGISTER_DATA_11 0xAB
typedef union {
    struct
    {
        uint8_t data_11_l : 8;
        uint8_t data_11_h : 8;
    };
    uint16_t word;
} as7343_data_11_reg_t;

#define SFE_AS7343_REGISTER_DATA_12 0xAD
typedef union {
    struct
    {
        uint8_t data_12_l : 8;
        uint8_t data_12_h : 8;
    };
    uint16_t word;
} as7343_data_12_reg_t;

#define SFE_AS7343_REGISTER_DATA_13 0xAF
typedef union {
    struct
    {
        uint8_t data_13_l : 8;
        uint8_t data_13_h : 8;
    };
    uint16_t word;
} as7343_data_13_reg_t;

#define SFE_AS7343_REGISTER_DATA_14 0xB1
typedef union {
    struct
    {
        uint8_t data_14_l : 8;
        uint8_t data_14_h : 8;
    };
    uint16_t word;
} as7343_data_14_reg_t;

#define SFE_AS7343_REGISTER_DATA_15 0xB3
typedef union {
    struct
    {
        uint8_t data_15_l : 8;
        uint8_t data_15_h : 8;
    };
    uint16_t word;
} as7343_data_15_reg_t;

#define SFE_AS7343_REGISTER_DATA_16 0xB5
typedef union {
    struct
    {
        uint8_t data_16_l : 8;
        uint8_t data_16_h : 8;
    };
    uint16_t word;
} as7343_data_16_reg_t;

#define SFE_AS7343_REGISTER_DATA_17 0xB7
typedef union {
    struct
    {
        uint8_t data_17_l : 8;
        uint8_t data_17_h : 8;
    };
    uint16_t word;
} as7343_data_17_reg_t;

#define SFE_AS7343_REGISTER_STATUS2 0x90
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
} as7343_status2_reg_t;

#define SFE_AS7343_REGISTER_STATUS3 0x91
typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t int_sp_l : 1;
        uint8_t int_sp_h : 1;
        uint8_t reserved_one : 2;
    };
    uint8_t word;
} as7343_status3_reg_t;

#define SFE_AS7343_REGISTER_STATUS4 0xBC
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
} as7343_status4_reg_t;

#define SFE_AS7343_REGISTER_STATUS5 0x93
typedef union {
    struct
    {
        uint8_t reserved : 2;
        uint8_t sint_smux : 1;
        uint8_t sint_fd : 1;
        uint8_t reserved_one : 4;
    };
    uint8_t word;
} as7343_data_status5_reg_t;

#define SFE_AS7343_REGISTER_CFG0 0xBF
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
} as7343_cfg0_reg_t;

#define SFE_AS7343_REGISTER_CFG1 0xC6
typedef union {
    struct
    {
        uint8_t again : 5;
        uint8_t reserved: 3;
    };
    uint8_t word;
} as7343_cfg1_reg_t;

#define SFE_AS7343_REGISTER_CFG3 0xC7
typedef union {
    struct
    {
        uint8_t reserved: 4;
        uint8_t again : 1;
        uint8_t reserved: 3;
    };
    uint8_t word;
} as7343_cfg3_reg_t;

#define SFE_AS7343_REGISTER_CFG6 0xF5
typedef union {
    struct
    {
        uint8_t reserved : 3;
        uint8_t smux_cmd: 2;
        uint8_t reserved_one : 3;
    };
    uint8_t word;
} as7343_cfg6_reg_t;

#define SFE_AS7343_REGISTER_CFG8 0xC9
typedef union {
    struct
    {
        uint8_t reserved : 6;
        uint8_t fifo_th: 2;
    };
    uint8_t word;
} as7343_cfg8_reg_t;

#define SFE_AS7343_REGISTER_CFG9 0xCA
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
} as7343_cfg9_reg_t;

#define SFE_AS7343_REGISTER_CFG10 0x65
typedef union {
    struct
    {
        uint8_t fd_pers : 3;
        uint8_t reserved : 5;
    };
    uint8_t word;
} as7343_cfg10_reg_t;

#define SFE_AS7343_REGISTER_PERS 0xCF
typedef union {
    struct
    {
        uint8_t PERS : 4;
        uint8_t reserved : 4;
    };
    uint8_t word;
} as7343_pers_reg_t;

#define SFE_AS7343_REGISTER_GPIO 0x6B
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
} as7343_gpio_reg_t;

#define SFE_AS7343_REGISTER_ASTEP 0xD4
typedef union {
    struct
    {
        uint8_t astep_l : 8;
        uint8_t astep_h : 8;
    };
    uint16_t word;
} as7343_astep_reg_t;

#define SFE_AS7343_REGISTER_CFG20 0xD6
typedef union {
    struct
    {
        uint8_t reserved : 5;
        uint8_t auto_smux : 2;
        uint8_t fd_fifo_8b : 1;
    };
    uint8_t word;
} as7343_cfg20_reg_t;

#define SFE_AS7343_REGISTER_LED 0xCD
typedef union {
    struct
    {
        uint8_t led_drive : 7;
        uint8_t led_act : 1;
    };
    uint8_t word;
} as7343_led_reg_t;

#define SFE_AS7343_REGISTER_AGC_GAIN_MAX 0xD7
typedef union {
    struct
    {
        uint8_t reserved : 4;
        uint8_t agc_fd_gain_max : 4;
    };
    uint8_t word;
} as7343_agc_gain_max_reg_t;

#define SFE_AS7343_REGISTER_AZ_CONFIG 0xDE
typedef union {
    struct
    {
        uint8_t at_nth_iteration : 8;
    };
    uint8_t word;
} as7343_az_config_reg_t;

#define SFE_AS7343_REGISTER_FD_TIME_1 0xE0
typedef union {
    struct
    {
        uint8_t fd_time_l : 8; // TODO: Unknown bit order
    };
    uint8_t word;
} as7343_fd_time_1_reg_t;


#define SFE_AS7343_REGISTER_FD_TIME_2 0xE2
typedef union {
    struct
    {
        uint8_t fd_time_h : 3; // TODO: Unkown big order
        uint8_t fd_gain : 5;
    };
    uint8_t word;
} as7343_fd_time_2_reg_t;

#define SFE_AS7343_REGISTER_FD_TIME_CFG0 0xDF
typedef union {
    struct
    {
        uint8_t reserved : 7;
        uint8_t fifo_write_fd : 1;
    };
    uint8_t word;
} as7343_fd_cfg0_reg_t;

#define SFE_AS7343_REGISTER_FD_STATUS 0xE3
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
} as7343_fd_status_reg_t;

#define SFE_AS7343_REGISTER_INTENAB 0xF9
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
} as7343_intenab_reg_t;

#define SFE_AS7343_REGISTER_CONTROL 0xFA
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
} as7343_control_reg_t;

#define SFE_AS7343_REGISTER_FIFO_MAP 0xFC
typedef union {
    struct
    {
        uint8_t astatus : 1;
        uint8_t fifo_write_ch5_data_fifo_write_ch0_data : 6;
        uint8_t reserved : 6;
    };
    uint8_t word;
} as7343_fifo_map_reg_t;

#define SFE_AS7343_REGISTER_FIFO_LVL 0xFD
typedef union {
    struct
    {
        uint8_t fifo_lvl : 8;
    };
    uint8_t word;
} as7343_fifo_lvl_reg_t;

#define SFE_AS7343_REGISTER_FDATA 0xFE
typedef union {
    struct
    {
        uint8_t fdata_l : 8;
        uint8_t fdata_h : 8;
    };
    uint16_t word;
} as7343_fifo_data_reg_t;

