#ifndef INSTRUCTIONS_TABLES_H_
#define INSTRUCTIONS_TABLES_H_

#include <stdint.h>

typedef void(*instruction_fn)(instruction_t*, cpu_t*);

extern uint8_t instruction_cycles[256];
extern uint8_t instruction_bytes[256];
extern instruction_fn instruction_table[256];

#endif

