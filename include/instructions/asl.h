#ifndef INCLUDE_INSTRUCTIONS_ASL_H_
#define INCLUDE_INSTRUCTIONS_ASL_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void asl_accumulator(instruction_t* self, cpu_t* cpu);
void asl_zero_page(instruction_t* self, cpu_t* cpu);
void asl_zero_page_x(instruction_t* self, cpu_t* cpu);
void asl_absolute(instruction_t* self, cpu_t* cpu);
void asl_absolute_x(instruction_t* self, cpu_t* cpu);

#endif
