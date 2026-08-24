#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <stdint.h>
#include "instructions/instruction_def.h"
#include "cpu.h"

instruction_t instruction_init(uint8_t opcode);
instruction_t get_instruction(cpu_t* cpu);

#endif
