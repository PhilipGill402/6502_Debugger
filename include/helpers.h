#ifndef INCLUDE_HELPERS_H_
#define INCLUDE_HELPERS_H_

#include <stdint.h>
#include "cpu.h"

#include <stdio.h>

static inline uint8_t read8(cpu_t* cpu, uint16_t addr) {
    return cpu->mem[addr];
}

static inline uint16_t read16(cpu_t* cpu, uint16_t addr) {
    return (cpu->mem[addr + 1] << 8) | cpu->mem[addr];
}

static inline void write8(cpu_t* cpu, uint16_t addr, uint8_t value) {
    cpu->mem[addr] = value;
}

static inline void push8(cpu_t* cpu, uint8_t value) {
    cpu->mem[STACK_START + cpu->sp] = value;
    cpu->sp--;
}

static inline void push16(cpu_t* cpu, uint16_t value) {
    push8(cpu, (uint8_t)(value >> 8));
    push8(cpu, (uint8_t)value);
}

static inline uint8_t pull8(cpu_t* cpu) {
    cpu->sp++;
    return cpu->mem[STACK_START + cpu->sp];
}

#endif
