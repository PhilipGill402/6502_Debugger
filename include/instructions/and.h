#ifndef INCLUDE_INSTRUCTIONS_ADC_H_
#define INCLUDE_INSTRUCTIONS_ADC_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void adc_immediate(instruction_t* self, cpu_t* cpu);
void adc_zero_page(instruction_t* self, cpu_t* cpu);
void adc_zero_page_x(instruction_t* self, cpu_t* cpu);
void adc_absolute(instruction_t* self, cpu_t* cpu);
void adc_absolute_x(instruction_t* self, cpu_t* cpu);
void adc_absolute_y(instruction_t* self, cpu_t* cpu);
void adc_indirect_x(instruction_t* self, cpu_t* cpu);
void adc_indirect_y(instruction_t* self, cpu_t* cpu);

#endif
