#ifndef INCLUDE_INSTRUCTIONS_BNE_H_
#define INCLUDE_INSTRUCTIONS_BNE_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bne_relative(instruction_t* self, cpu_t* cpu);

#endif
