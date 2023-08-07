#pragma once
#include <cstdint>
#include <stdint.h>

// LITTLE ENDIAN
#define AS7343_ONLY_ADDR 0x39

#define SFE_AS7343_REGISTER_XXX 0xXXX
typedef union {
    struct
    {
        uint8_t XXX : 4;
    };
    uint8_t word;
} as7343_XXX_reg_t;

#define SFE_AS7343_REGISTER_AUXID 0x58
typedef union {
    struct
    {
        uint8_t aux_id : 4;
        uint8_t reserved : 4;
    };
    uint8_t word;
} as7343_aux_id_reg_t;

#define SFE_AS7343_REGISTER_REV_ID 0x59
typedef union {
    struct
    {
        uint8_t rev_id : 3;
        uint8_t reserved : 5;
    };
    uint8_t word;
} as7343_rev_id_reg_t;

#define SFE_AS7343_REGISTER_ID 0xID
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
        uint8_t w_en : 1;
        uint8_t smux_en : 1;
        uint8_t reserved_one : 1;
        uint8_t fden : 1;
        uint8_t reserved_two : 1;
        uint8_t enable : 1;
    };
    uint8_t word;
} as7343_enable_reg_t;

#define SFE_AS7343_REGISTER_WTIME 0xXXX
typedef union {
    struct
    {
        uint8_t XXX : 4;
    };
    uint8_t word;
} as7343_XXX_reg_t;

