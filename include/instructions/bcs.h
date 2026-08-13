#ifndef INCLUDE_INSTRUCTIONS_BCS_H_
#define INCLUDE_INSTRUCTIONS_BCS_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bcs_relative(instruction_t* self, cpu_t* cpu);

#endif
