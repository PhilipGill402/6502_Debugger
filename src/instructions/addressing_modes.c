#include "instructions/addressing_modes.h"
#include "helpers.h"

uint16_t get_effective_address(cpu_t* cpu, addressing_mode_t mode) {
    switch (mode) {
        case ADDRESS_IMMEDIATE: {
            return 0;
        }
        case ADDRESS_ACCUMULATOR: {
            return 0;
        }
        case ADDRESS_IMPLIED: {
            return 0;
        }
        case ADDRESS_ZERO_PAGE: {
            return read8(cpu, cpu->pc++);
        }
        case ADDRESS_ZERO_PAGE_X: {
            return read8(cpu, cpu->pc++) + cpu->x;
        }
        case ADDRESS_ZERO_PAGE_Y: {
            return read8(cpu, cpu->pc++) + cpu->y;
        }
        case ADDRESS_RELATIVE: {
            int8_t offset = (int8_t)read8(cpu, cpu->pc++);
            return cpu->pc + offset;
        }
        case ADDRESS_ABSOLUTE: {
            uint16_t addr = read16(cpu, cpu->pc++);
            cpu->pc++;
            return addr;
        }
        case ADDRESS_ABSOLUTE_X: {
            uint16_t addr = read16(cpu, cpu->pc++) + cpu->x;
            cpu->pc++;
            return addr;
        }
        case ADDRESS_ABSOLUTE_Y: {
            uint16_t addr = read16(cpu, cpu->pc++) + cpu->y;
            cpu->pc++;
            return addr;
        }
        case ADDRESS_INDIRECT: {
            uint16_t indirect_addr = read16(cpu, cpu->pc++);
            cpu->pc++;
            return read16(cpu, indirect_addr);
        }
        case ADDRESS_INDEXED_INDIRECT: {
            uint8_t indirect_addr = read8(cpu, cpu->pc++) + cpu->x;
            return read16(cpu, indirect_addr);
        }
        case ADDRESS_INDIRECT_INDEXED: {
            uint8_t indirect_addr = read8(cpu, cpu->pc++);
            return read16(cpu, indirect_addr) + cpu->y;
        }
    }
}

uint8_t get_value(cpu_t* cpu, addressing_mode_t mode) {
    switch (mode) {
        case ADDRESS_IMPLIED: {
            return 0;
        }
        case ADDRESS_IMMEDIATE: {
            return read8(cpu, cpu->pc++);
        }
        case ADDRESS_ACCUMULATOR: {
            return cpu->a;
        }
        case ADDRESS_ZERO_PAGE: {
            return read8(cpu, cpu->pc++);
        }
        case ADDRESS_ZERO_PAGE_X: {
            uint8_t addr = read8(cpu, cpu->pc++) + cpu->x;
            return read8(cpu, addr);
        }
        case ADDRESS_ZERO_PAGE_Y: {
            uint8_t addr = read8(cpu, cpu->pc++) + cpu->y;
            return read8(cpu, addr);
        }
        case ADDRESS_RELATIVE: {
            int8_t offset = (int8_t)read8(cpu, cpu->pc++);
            return read8(cpu, cpu->pc + offset);
        }
        case ADDRESS_ABSOLUTE: {
            uint16_t addr = read16(cpu, cpu->pc++);
            cpu->pc++;
            return read8(cpu, addr);
        }
        case ADDRESS_ABSOLUTE_X: {
            uint16_t addr = read16(cpu, cpu->pc++) + cpu->x;
            cpu->pc++;
            return read8(cpu, addr);
        }
        case ADDRESS_ABSOLUTE_Y: {
            uint16_t addr = read16(cpu, cpu->pc++) + cpu->y;
            cpu->pc++;
            return read8(cpu, addr);
        }
        case ADDRESS_INDIRECT: {
            uint16_t indirect_addr = read16(cpu, cpu->pc++);
            cpu->pc++;
            uint16_t addr = read16(cpu, indirect_addr);
            return read8(cpu, addr);
        }
        case ADDRESS_INDEXED_INDIRECT: {
            uint8_t indirect_addr = read8(cpu, cpu->pc++) + cpu->x;
            uint16_t addr = read16(cpu, indirect_addr);
            return read8(cpu, addr);
        }
        case ADDRESS_INDIRECT_INDEXED: {
            uint8_t indirect_addr = read8(cpu, cpu->pc++);
            uint16_t addr = read16(cpu, indirect_addr) + cpu->y;
            return read8(cpu, addr);
        }
    }
}
