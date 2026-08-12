#ifndef INCLUDE_INSTRUCTIONS_LDX_H_
#define INCLUDE_INSTRUCTIONS_LDX_H_

#include "instructions/instruction_def.h"
#include "cpu.h"

void ldx_immediate(instruction_t* self, cpu_t* cpu);
void ldx_zero_page(instruction_t* self, cpu_t* cpu);
void ldx_zero_page_y(instruction_t* self, cpu_t* cpu);
void ldx_absolute(instruction_t* self, cpu_t* cpu);
void ldx_absolute_y(instruction_t* self, cpu_t* cpu);

#endif
