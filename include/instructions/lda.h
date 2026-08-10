#ifndef INCLUDE_INSTRUCTIONS_LDA_H_
#define INCLUDE_INSTRUCTIONS_LDA_H_

#include "cpu.h"

void lda_immediate(cpu_t* cpu);
void lda_zero_page(cpu_t* cpu);
void lda_zero_page_x(cpu_t* cpu);
void lda_absolute(cpu_t* cpu);
void lda_absolute_x(cpu_t* cpu);
void lda_absolute_y(cpu_t* cpu);
void lda_indirect_x(cpu_t* cpu);
void lda_indirect_y(cpu_t* cpu);

#endif
