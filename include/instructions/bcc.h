#ifndef INCLUDE_INSTRUCTIONS_BCC_H_
#define INCLUDE_INSTRUCTIONS_BCC_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bcc_relative(instruction_t* self, cpu_t* cpu);

#endif
