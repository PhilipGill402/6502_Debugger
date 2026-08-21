#ifndef INCLUDE_HELPERS_H_
#define INCLUDE_HELPERS_H_

#include <stdint.h>
#include "cpu.h"

#include <stdio.h>

static inline uint8_t read8(cpu_t* cpu, uint16_t addr) {
    return cpu->mem[addr];
}

static inline uint16_t read16(cpu_t* cpu, uint16_t addr) {
    return (cpu->mem[(uint16_t)(addr + 1)] << 8) | cpu->mem[addr];
}

static inline void write8(cpu_t* cpu, uint16_t addr, uint8_t value) {
    cpu->mem[addr] = value;
}

static inline void write16(cpu_t* cpu, uint16_t addr, uint16_t value) {
    cpu->mem[addr] = (uint8_t)value;
    cpu->mem[(uint16_t)(addr+1)] = (uint8_t)(value >> 8);
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

static inline uint16_t pull16(cpu_t* cpu) {
    uint8_t low = pull8(cpu);
    uint8_t high = pull8(cpu);

    return ((uint16_t)high << 8) | low;
}

#endif
