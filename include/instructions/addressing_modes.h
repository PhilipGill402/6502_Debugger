#ifndef INSTRUCTIONS_ADDRESSING_MODES_H_
#define INSTRUCTIONS_ADDRESSING_MODES_H_

#include <stdint.h>
#include "cpu.h"

typedef enum {
    ADDRESS_IMMEDIATE;
    ADDRESS_ZERO_PAGE;
    ADDRESS_ZERO_PAGE_X;
    ADDRESS_ZERO_PAGE_Y;
    ADDRESS_RELATIVE;
    ADDRESS_ABSOLUTE;
    ADDRESS_ABSOLUTE_X;
    ADDRESS_ABSOLUTE_Y;
    ADDRESS_INDIRECT;
    ADDRESS_INDEXED_INDIRECT;
    ADDRESS_INDIRECT_INDEXED;
} addressing_modes_t;

uint8_t address(cpu_t* cpu, addressing_mode_t mode);

#endif
