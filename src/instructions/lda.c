#include "instructions/lda.h"

#include <stdio.h>

static void lda_update_status(cpu_t* cpu) {
    if (cpu->a == 0)
        SET_ZERO(cpu->status);

    if (cpu->a & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void lda_immediate(cpu_t* cpu) {
    cpu->pc++; // skip opcode
    uint8_t value = cpu->mem[cpu->pc++]; // value to be loaded in
    
    cpu->a = value;

    lda_update_status(cpu); 
}

void lda_zero_page(cpu_t* cpu) {
    cpu->pc++; // skip opcode
    uint8_t addr = cpu->mem[cpu->pc++]; // zero page addr
    
    // because we only read one byte for the addr it will always be in the zero page
    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

void lda_zero_page_x(cpu_t* cpu) {
    cpu->pc++; // skip opcode
    uint8_t base_addr = cpu->mem[cpu->pc++]; // base addr to be added to
    uint8_t addr = base_addr + cpu->x; // because we use 'uint8_t' we dont have to worry about overflow logic

    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

void lda_absolute(cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint8_t low_byte = cpu->mem[cpu->pc++];
    uint8_t high_byte = cpu->mem[cpu->pc++];
    uint16_t addr = (high_byte << 8) | low_byte;

    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

// TODO: research page boundary crossing
void lda_absolute_x(cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint8_t low_byte = cpu->mem[cpu->pc++];
    uint8_t high_byte = cpu->mem[cpu->pc++];
    uint16_t base_addr = (high_byte << 8) | low_byte;
    uint16_t addr = base_addr + cpu->x;
    
    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

// TODO: research page boundary crossing
void lda_absolute_y(cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint8_t low_byte = cpu->mem[cpu->pc++];
    uint8_t high_byte = cpu->mem[cpu->pc++];
    uint16_t base_addr = (high_byte << 8) | low_byte;
    uint16_t addr = base_addr + cpu->y;
    
    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

void lda_indirect_x(cpu_t* cpu) {
    cpu->pc++; // skip opcode

    uint8_t base_addr = cpu->mem[cpu->pc++];
    uint8_t indirect_addr = base_addr + cpu->x;
    uint8_t addr = cpu->mem[indirect_addr];

    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

void lda_indirect_y(cpu_t* cpu) {
    cpu->pc++; // skip opcode

    uint8_t indirect_addr = cpu->mem[cpu->pc++];
    uint8_t base_addr = cpu->mem[indirect_addr];
    uint8_t addr = base_addr + cpu->y;

    cpu->a = cpu->mem[addr];

    lda_update_status(cpu);
}

