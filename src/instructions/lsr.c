#include "instructions/lsr.h"

#include <stdint.h>
#include "helpers.h"

static void lsr_update_status(cpu_t* cpu, uint8_t preshift_value, uint8_t postshift_value) {
    if (preshift_value & 0x0001)
        SET_CARRY(cpu->status);
    else
        CLEAR_CARRY(cpu->status);
    
    if (!postshift_value)
        SET_ZERO(cpu->status);

    if (postshift_value & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void lsr_accumulator(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t preshift = cpu->a;
    uint8_t postshift = preshift >> 1;

    cpu->a = postshift;

    lsr_update_status(cpu, preshift, postshift);
}

void lsr_zero_page(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t addr = read8(cpu->pc++);
    uint8_t preshift = read8(addr);
    uint8_t postshift = preshift >> 1;

    write8(addr, postshift);

    lsr_update_status(cpu, preshift, postshift);
}

void lsr_zero_page_x(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t addr = read8(cpu->pc++) + cpu->x;
    uint8_t preshift = read8(addr);
    uint8_t postshift = preshift >> 1;

    write8(addr, postshift);

    lsr_update_status(cpu, preshift, postshift);
}

void lsr_absolute(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint16_t addr = read16(cpu->pc++);
    cpu->pc++;

    uint8_t preshift = read8(addr);
    uint8_t postshift = preshift >> 1;

    write8(addr, postshift);

    lsr_update_status(cpu, preshift, postshift);
}

void lsr_absolute_x(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint16_t addr = read16(cpu->pc++) + cpu->x;
    cpu->pc++;

    uint8_t preshift = read8(addr);
    uint8_t postshift = preshift >> 1;

    write8(addr, postshift);

    lsr_update_status(cpu, preshift, postshift);
}

