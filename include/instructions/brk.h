#ifndef INCLUDE_INSTRUCTIONS_BRK_H_
#define INCLUDE_INSTRUCTIONS_BRK_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void brk_implied(instruction_t* self, cpu_t* cpu);

#endif
