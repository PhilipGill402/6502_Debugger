#include "helpers.h"
#include "cli/watchlist.h"

uint8_t read8(cpu_t* cpu, uint16_t addr) {
    watch_point_activate(addr); 

    return cpu->mem[addr];
}

uint16_t read16(cpu_t* cpu, uint16_t addr) {
    watch_point_activate(addr);
    watch_point_activate(addr + 1);

    return (cpu->mem[(uint16_t)(addr + 1)] << 8) | cpu->mem[addr];
}

void write8(cpu_t* cpu, uint16_t addr, uint8_t value) {
    watch_point_activate(addr);

    cpu->mem[addr] = value;
}

void write16(cpu_t* cpu, uint16_t addr, uint16_t value) {
    watch_point_activate(addr);
    watch_point_activate(addr + 1);

    cpu->mem[addr] = (uint8_t)value;
    cpu->mem[(uint16_t)(addr+1)] = (uint8_t)(value >> 8);
}
