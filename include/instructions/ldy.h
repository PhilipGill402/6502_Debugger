#ifndef INCLUDE_INSTRUCTIONS_LDY_H_
#define INCLUDE_INSTRUCTIONS_LDY_H_

#include "instructions/instruction_def.h"
#include "cpu.h"

void ldy_immediate(instruction_t* self, cpu_t* cpu);
void ldy_zero_page(instruction_t* self, cpu_t* cpu);
void ldy_zero_page_x(instruction_t* self, cpu_t* cpu);
void ldy_absolute(instruction_t* self, cpu_t* cpu);
void ldy_absolute_x(instruction_t* self, cpu_t* cpu);

#endif
