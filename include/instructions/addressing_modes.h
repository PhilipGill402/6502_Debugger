#ifndef INSTRUCTIONS_ADDRESSING_MODES_H_
#define INSTRUCTIONS_ADDRESSING_MODES_H_

#include <stdint.h>
#include "cpu.h"

typedef enum {
    ADDRESS_IMPLIED,
    ADDRESS_ACCUMULATOR,
    ADDRESS_IMMEDIATE,
    ADDRESS_ZERO_PAGE,
    ADDRESS_ZERO_PAGE_X,
    ADDRESS_ZERO_PAGE_Y,
    ADDRESS_RELATIVE,
    ADDRESS_ABSOLUTE,
    ADDRESS_ABSOLUTE_X,
    ADDRESS_ABSOLUTE_Y,
    ADDRESS_INDIRECT,
    ADDRESS_INDEXED_INDIRECT,
    ADDRESS_INDIRECT_INDEXED,
} addressing_mode_t;

uint16_t get_effective_address(cpu_t* cpu, addressing_mode_t mode);
uint8_t get_value(cpu_t* cpu, addressing_mode_t mode);

#endif
