#ifndef INCLUDE_INSTRUCTIONS_BPL_H_
#define INCLUDE_INSTRUCTIONS_BPL_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bpl_relative(instruction_t* self, cpu_t* cpu);

#endif
