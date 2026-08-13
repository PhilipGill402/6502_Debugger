#ifndef INCLUDE_INSTRUCTIONS_INSTRUCTION_DEF_H_
#define INCLUDE_INSTRUCTIONS_INSTRUCTION_DEF_H_

#include <stdint.h>

#include "instructions/addressing_modes.h"
#include "cpu.h"

typedef struct instruction {
    uint8_t opcode;
    uint8_t bytes;
    uint8_t cycles;
    addressing_mode_t mode; 
    void (*execute)(struct instruction*, cpu_t*, addressing_mode_t);
} instruction_t;

#endif 
