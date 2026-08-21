#ifndef TEST_TEST_
#define TEST_TEST_

#include <stdint.h>

#define BRK_IMPLIED            0x00
#define ORA_INDEXED_INDIRECT   0x01
#define ORA_ZERO_PAGE          0x05
#define ASL_ZERO_PAGE          0x06
#define PHP_IMPLIED            0x08
#define ORA_IMMEDIATE          0x09
#define ASL_ACCUMULATOR        0x0A
#define ORA_ABSOLUTE           0x0D
#define ASL_ABSOLUTE           0x0E

#define BPL_RELATIVE           0x10
#define ORA_INDIRECT_INDEXED   0x11
#define ORA_ZERO_PAGE_X        0x15
#define ASL_ZERO_PAGE_X        0x16
#define CLC_IMPLIED            0x18
#define ORA_ABSOLUTE_Y         0x19
#define ORA_ABSOLUTE_X         0x1D
#define ASL_ABSOLUTE_X         0x1E

#define JSR_ABSOLUTE           0x20
#define AND_INDEXED_INDIRECT   0x21
#define BIT_ZERO_PAGE          0x24
#define AND_ZERO_PAGE          0x25
#define ROL_ZERO_PAGE          0x26
#define PLP_IMPLIED            0x28
#define AND_IMMEDIATE          0x29
#define ROL_ACCUMULATOR        0x2A
#define BIT_ABSOLUTE           0x2C
#define AND_ABSOLUTE           0x2D
#define ROL_ABSOLUTE           0x2E

#define BMI_RELATIVE           0x30
#define AND_INDIRECT_INDEXED   0x31
#define AND_ZERO_PAGE_X        0x35
#define ROL_ZERO_PAGE_X        0x36
#define SEC_IMPLIED            0x38
#define AND_ABSOLUTE_Y         0x39
#define AND_ABSOLUTE_X         0x3D
#define ROL_ABSOLUTE_X         0x3E

#define RTI_IMPLIED            0x40
#define EOR_INDEXED_INDIRECT   0x41
#define EOR_ZERO_PAGE          0x45
#define LSR_ZERO_PAGE          0x46
#define PHA_IMPLIED            0x48
#define EOR_IMMEDIATE          0x49
#define LSR_ACCUMULATOR        0x4A
#define JMP_ABSOLUTE           0x4C
#define EOR_ABSOLUTE           0x4D
#define LSR_ABSOLUTE           0x4E

#define BVC_RELATIVE           0x50
#define EOR_INDIRECT_INDEXED   0x51
#define EOR_ZERO_PAGE_X        0x55
#define LSR_ZERO_PAGE_X        0x56
#define CLI_IMPLIED            0x58
#define EOR_ABSOLUTE_Y         0x59
#define EOR_ABSOLUTE_X         0x5D
#define LSR_ABSOLUTE_X         0x5E

#define RTS_IMPLIED            0x60
#define ADC_INDEXED_INDIRECT   0x61
#define ADC_ZERO_PAGE          0x65
#define ROR_ZERO_PAGE          0x66
#define PLA_IMPLIED            0x68
#define ADC_IMMEDIATE          0x69
#define ROR_ACCUMULATOR        0x6A
#define JMP_INDIRECT           0x6C
#define ADC_ABSOLUTE           0x6D
#define ROR_ABSOLUTE           0x6E

#define BVS_RELATIVE           0x70
#define ADC_INDIRECT_INDEXED   0x71
#define ADC_ZERO_PAGE_X        0x75
#define ROR_ZERO_PAGE_X        0x76
#define SEI_IMPLIED            0x78
#define ADC_ABSOLUTE_Y         0x79
#define ADC_ABSOLUTE_X         0x7D
#define ROR_ABSOLUTE_X         0x7E

#define STA_INDEXED_INDIRECT   0x81
#define STY_ZERO_PAGE          0x84
#define STA_ZERO_PAGE          0x85
#define STX_ZERO_PAGE          0x86
#define DEY_IMPLIED            0x88
#define TXA_IMPLIED            0x8A
#define STY_ABSOLUTE           0x8C
#define STA_ABSOLUTE           0x8D
#define STX_ABSOLUTE           0x8E

#define BCC_RELATIVE           0x90
#define STA_INDIRECT_INDEXED   0x91
#define STY_ZERO_PAGE_X        0x94
#define STA_ZERO_PAGE_X        0x95
#define STX_ZERO_PAGE_Y        0x96
#define TYA_IMPLIED            0x98
#define STA_ABSOLUTE_Y         0x99
#define TXS_IMPLIED            0x9A
#define STA_ABSOLUTE_X         0x9D

#define LDY_IMMEDIATE          0xA0
#define LDA_INDEXED_INDIRECT   0xA1
#define LDX_IMMEDIATE          0xA2
#define LDY_ZERO_PAGE          0xA4
#define LDA_ZERO_PAGE          0xA5
#define LDX_ZERO_PAGE          0xA6
#define TAY_IMPLIED            0xA8
#define LDA_IMMEDIATE          0xA9
#define TAX_IMPLIED            0xAA
#define LDY_ABSOLUTE           0xAC
#define LDA_ABSOLUTE           0xAD
#define LDX_ABSOLUTE           0xAE

#define BCS_RELATIVE           0xB0
#define LDA_INDIRECT_INDEXED   0xB1
#define LDY_ZERO_PAGE_X        0xB4
#define LDA_ZERO_PAGE_X        0xB5
#define LDX_ZERO_PAGE_Y        0xB6
#define CLV_IMPLIED            0xB8
#define LDA_ABSOLUTE_Y         0xB9
#define TSX_IMPLIED            0xBA
#define LDY_ABSOLUTE_X         0xBC
#define LDA_ABSOLUTE_X         0xBD
#define LDX_ABSOLUTE_Y         0xBE

#define CPY_IMMEDIATE          0xC0
#define CMP_INDEXED_INDIRECT   0xC1
#define CPY_ZERO_PAGE          0xC4
#define CMP_ZERO_PAGE          0xC5
#define DEC_ZERO_PAGE          0xC6
#define INY_IMPLIED            0xC8
#define CMP_IMMEDIATE          0xC9
#define DEX_IMPLIED            0xCA
#define CPY_ABSOLUTE           0xCC
#define CMP_ABSOLUTE           0xCD
#define DEC_ABSOLUTE           0xCE

#define BNE_RELATIVE           0xD0
#define CMP_INDIRECT_INDEXED   0xD1
#define CMP_ZERO_PAGE_X        0xD5
#define DEC_ZERO_PAGE_X        0xD6
#define CLD_IMPLIED            0xD8
#define CMP_ABSOLUTE_Y         0xD9
#define CMP_ABSOLUTE_X         0xDD
#define DEC_ABSOLUTE_X         0xDE

#define CPX_IMMEDIATE          0xE0
#define SBC_INDEXED_INDIRECT   0xE1
#define CPX_ZERO_PAGE          0xE4
#define SBC_ZERO_PAGE          0xE5
#define INC_ZERO_PAGE          0xE6
#define INX_IMPLIED            0xE8
#define SBC_IMMEDIATE          0xE9
#define NOP_IMPLIED            0xEA
#define CPX_ABSOLUTE           0xEC
#define SBC_ABSOLUTE           0xED
#define INC_ABSOLUTE           0xEE

#define BEQ_RELATIVE           0xF0
#define SBC_INDIRECT_INDEXED   0xF1
#define SBC_ZERO_PAGE_X        0xF5
#define INC_ZERO_PAGE_X        0xF6
#define SED_IMPLIED            0xF8
#define SBC_ABSOLUTE_Y         0xF9
#define SBC_ABSOLUTE_X         0xFD
#define INC_ABSOLUTE_X         0xFE

void test();

#endif
