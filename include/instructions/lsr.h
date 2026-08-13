#ifndef INCLUDE_INSTRUCTIONS_LSR_H_
#define INCLUDE_INSTRUCTIONS_LSR_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void lsr_accumulator(instruction_t* self, cpu_t* cpu);
void lsr_zero_page(instruction_t* self, cpu_t* cpu);
void lsr_zero_page_x(instruction_t* self, cpu_t* cpu);
void lsr_absolute(instruction_t* self, cpu_t* cpu);
void lsr_absolute_x(instruction_t* self, cpu_t* cpu);

#endif
