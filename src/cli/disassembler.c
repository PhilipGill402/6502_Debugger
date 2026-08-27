#include "cli/disassembler.h"
#include "instructions/tables.h"
#include "instructions/addressing_modes.h"
#include "helpers.h"
#include <stdlib.h>

char* disassemble_line(cpu_t* cpu, uint16_t* addr) {
    uint8_t opcode = read8(cpu, *addr);
    uint8_t bytes = instruction_bytes[opcode];
    addressing_mode_t mode = instruction_addressing_mode[opcode];
    const char* name = instruction_names[opcode];
    char* buffer = malloc(BUFFER_SIZE);

    switch (mode) {
        case ADDRESS_IMMEDIATE: {
            uint8_t arg = read8(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s #%d", *addr, name, arg);
            break;
        }
        case ADDRESS_ACCUMULATOR: {
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s A", *addr, name);
            break;
        }
        case ADDRESS_IMPLIED: {
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s", *addr, name);
            break;
        }
        case ADDRESS_ZERO_PAGE: {
            uint8_t zero_addr = read8(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d", *addr, name, zero_addr);
            break;
        }
        case ADDRESS_ZERO_PAGE_X: {
            uint8_t zero_addr = read8(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d,X", *addr, name, zero_addr);
            break;
        }
        case ADDRESS_ZERO_PAGE_Y: {
            uint8_t zero_addr = read8(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d,Y", *addr, name, zero_addr);
            break;
        }
        case ADDRESS_RELATIVE: {
            int8_t offset = (int8_t)read8(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s %d", *addr, name, (uint16_t)(*addr + bytes + offset));
            break;
        }
        case ADDRESS_ABSOLUTE: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d", *addr, name, arg);
            break;
        }
        case ADDRESS_ABSOLUTE_X: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d,X", *addr, name, arg);
            break;
        }
        case ADDRESS_ABSOLUTE_Y: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s $%d,Y", *addr, name, arg);
            break;
        }
        case ADDRESS_INDIRECT: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s (%d)", *addr, name, arg);
            break;
        }
        case ADDRESS_INDEXED_INDIRECT: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s ($%d,X)", *addr, name, arg);
            break;
        }
        case ADDRESS_INDIRECT_INDEXED: {
            uint16_t arg = read16(cpu, *addr + 1);
            snprintf(buffer, BUFFER_SIZE, "0x%04x: %s ($%d),Y", *addr, name, arg);
            break;
        }
    }

    *addr += bytes;
    return buffer;
}
