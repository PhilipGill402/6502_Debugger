#ifndef INSTRUCTIONS_TABLES_H_
#define INSTRUCTIONS_TABLES_H_

#include <stdint.h>

#include "instructions/instruction_def.h"
#include "instructions/addressing_modes.h"
#include "cpu.h"

typedef void(*instruction_fn)(instruction_t*, cpu_t*, addressing_mode_t);

extern uint8_t instruction_cycles[256];
extern uint8_t instruction_bytes[256];
extern instruction_fn instruction_table[256];
extern addressing_mode_t instruction_addressing_mode[256];

#endif

