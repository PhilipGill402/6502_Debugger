#ifndef INCLUDE_INSTRUCTIONS_BEQ_H_
#define INCLUDE_INSTRUCTIONS_BEQ_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void beq_relative(instruction_t* self, cpu_t* cpu);

#endif
