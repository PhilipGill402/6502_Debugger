#ifndef INCLUDE_INSTRUCTIONS_INSTRUCTION_DEF_H_
#define INCLUDE_INSTRUCTIONS_INSTRUCTION_DEF_H_

#include <stdint.h>
#include "cpu.h"

typedef struct instruction {
    uint8_t opcode;
    uint8_t bytes;
    uint8_t cycles;
    
    void (*execute)(struct instruction*, cpu_t*);
} instruction_t;

#endif 
