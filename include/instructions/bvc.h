#ifndef INCLUDE_INSTRUCTIONS_BVC_H_
#define INCLUDE_INSTRUCTIONS_BVC_H_

#include "instructions/instruction_defs.h"
#include "cpu.h"

void bvc_relative(instruction_t* self, cpu_t* cpu);

#endif
