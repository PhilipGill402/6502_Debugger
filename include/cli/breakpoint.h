#ifndef INCLUDE_CLI_BREAKPOINT_H_
#define INCLUDE_CLI_BREAKPOINT_H_

#include <stdint.h>

#define MAX_BREAKPOINTS 64

typedef struct {
    uint16_t addr;
} breakpoint_t;

void add_breakpoint(uint16_t addr);
uint8_t is_breakpoint(uint16_t pc);

extern breakpoint_t breakpoint_table[MAX_BREAKPOINTS];
extern uint8_t breakpoint_count;

#endif
