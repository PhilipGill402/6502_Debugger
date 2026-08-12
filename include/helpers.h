#ifndef INCLUDE_HELPERS_H_
#define INCLUDE_HELPERS_H_

#include <stdint.h>
#include "cpu.h"

static inline uint8_t read8(cpu_t* cpu, uint16_t addr) {
    return cpu->mem[addr];
}

static inline uint16_t read16(cpu_t* cpu, uint16_t addr) {
    return cpu->mem[((addr + 1) << 8) | addr];
}

static inline void write8(cpu_t* cpu, uint16_t addr, uint8_t value) {
    cpu->mem[addr] = value;
}

#endif
