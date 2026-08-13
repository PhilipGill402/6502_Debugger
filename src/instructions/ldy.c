#include "instructions/ldy.h"
#include "helpers.h"

#include <stdio.h>

static void ldy_update_status(cpu_t* cpu) {
    if (cpu->y == 0)
        SET_ZERO(cpu->status);

    if (cpu->y & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void ldy_immediate(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t value = read8(cpu, cpu->pc++);
    cpu->y = value;

    ldy_update_status(cpu); 
}

void ldy_zero_page(instruction_t* self, cpu_t* cpu) {
    (void)self; 
    cpu->pc++; // skip opcode
    uint8_t addr = read8(cpu, cpu->pc++); // zero page addr
    
    // because we only read one byte for the addr it will always be in the zero page
    cpu->y = read8(cpu, addr); 

    ldy_update_status(cpu);
}

void ldy_zero_page_x(instruction_t* self, cpu_t* cpu) {
    (void)self; 
    cpu->pc++; // skip opcode
    uint8_t base_addr = read8(cpu, cpu->pc++); // base addr to be added to
    uint8_t addr = base_addr + cpu->x; // because we use 'uint8_t' we dont have to worry about overflow logic
    
    cpu->y = read8(cpu, addr);

    ldy_update_status(cpu);
}

void ldy_absolute(instruction_t* self, cpu_t* cpu) {
    (void)self; 
    cpu->pc++; // skip opcode

    uint16_t addr = read16(cpu, cpu->pc++);
    cpu->pc++; // increment one more time as we are reading 2 bytes

    cpu->y = read8(cpu, addr);

    ldy_update_status(cpu);
}

void ldy_absolute_x(instruction_t* self, cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint16_t base_addr = read16(cpu, cpu->pc++);
    cpu->pc++; // increment one more time as we are reading 2 bytes
    uint16_t addr = base_addr + cpu->x;
    
    // checking if the page boundary is crossed
    if ((base_addr & 0xFF00) != (addr & 0xFF00))
        self->cycles++;

    cpu->y = read8(cpu, addr);

    ldy_update_status(cpu);
}

