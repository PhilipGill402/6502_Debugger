#ifndef INCLUDE_INSTRUCTIONS_BIT_H_
#define INCLUDE_INSTRUCTIONS_BIT_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bit_zero_page(instruction_t* self, cpu_t* cpu);
void bit_absolute(instruction_t* self, cpu_t* cpu);

#endif
