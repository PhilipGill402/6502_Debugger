#ifndef INCLUDE_INSTRUCTIONS_LDA_H_
#define INCLUDE_INSTRUCTIONS_LDA_H_

#include "cpu.h"
#include "instructions/instruction_def.h"

void lda_immediate(instruction_t* self, cpu_t* cpu);
void lda_zero_page(instruction_t* self, cpu_t* cpu);
void lda_zero_page_x(instruction_t* self, cpu_t* cpu);
void lda_absolute(instruction_t* self, cpu_t* cpu);
void lda_absolute_x(instruction_t* self, cpu_t* cpu);
void lda_absolute_y(instruction_t* self, cpu_t* cpu);
void lda_indirect_x(instruction_t* self, cpu_t* cpu);
void lda_indirect_y(instruction_t* self, cpu_t* cpu);

#endif
