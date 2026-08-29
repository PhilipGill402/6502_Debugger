#ifndef INCLUDE_HELPERS_H_
#define INCLUDE_HELPERS_H_

#include <stdint.h>
#include "cpu.h"

#include <stdio.h>

uint8_t read8(cpu_t* cpu, uint16_t addr);
uint16_t read16(cpu_t* cpu, uint16_t addr);
void write8(cpu_t* cpu, uint16_t addr, uint8_t value);
void write16(cpu_t* cpu, uint16_t addr, uint16_t value);

static inline void push8(cpu_t* cpu, uint8_t value) {
    write8(cpu, STACK_START + cpu->sp, value);
    cpu->sp--;
}

static inline void push16(cpu_t* cpu, uint16_t value) {
    push8(cpu, (uint8_t)(value >> 8));
    push8(cpu, (uint8_t)value);
}

static inline uint8_t pull8(cpu_t* cpu) {
    cpu->sp++;
    return read8(cpu, STACK_START + cpu->sp);
}

static inline uint16_t pull16(cpu_t* cpu) {
    uint8_t low = pull8(cpu);
    uint8_t high = pull8(cpu);

    return ((uint16_t)high << 8) | low;
}

#endif
