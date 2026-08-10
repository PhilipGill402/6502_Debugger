#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <stdint.h>
#include "cpu.h"

typedef struct {
    uint8_t opcode;
    uint8_t bytes;
    uint8_t cycles;
    
    void (*execute)(cpu_t*);
} instruction_t;

instruction_t instruction_init(uint8_t opcode);

#endif
