#include "instructions/instructions.h"

#include <stdio.h>
#include "instructions/tables.h"

instruction_t instruction_init(uint8_t opcode) {
    instruction_t ins = { 
        .opcode = opcode,
        .bytes = instruction_bytes[opcode],
        .cycles = instruction_cycles[opcode],
        .mode = instruction_addressing_mode[opcode],
        .execute = instruction_table[opcode],
    }; 
    
    return ins;
}

