#include "instructions/lda.h"

#include <stdio.h>
#include "helpers.h"

static void lda_update_status(cpu_t* cpu) {
    if (cpu->a == 0)
        SET_ZERO(cpu->status);

    if (cpu->a & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void lda_immediate(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t value = read8(cpu, cpu->pc++);
    cpu->a = value;

    lda_update_status(cpu); 
}

void lda_zero_page(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    uint8_t addr = read8(cpu, cpu->pc++); // zero page addr
    
    // because we only read one byte for the addr it will always be in the zero page
    cpu->a = read8(cpu, addr); 

    lda_update_status(cpu);
}

void lda_zero_page_x(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    uint8_t base_addr = read8(cpu, cpu->pc++); // base addr to be added to
    uint8_t addr = base_addr + cpu->x; // because we use 'uint8_t' we dont have to worry about overflow logic

    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

void lda_absolute(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint16_t addr = read16(cpu, cpu->pc++);
    cpu->pc++; // increment one more time as we are reading 2 bytes

    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

void lda_absolute_x(instruction_t* self, cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint16_t base_addr = read16(cpu, cpu->pc++);
    cpu->pc++; // increment one more time as we are reading 2 bytes
    uint16_t addr = base_addr + cpu->x;
    
    // checking if the page boundary is crossed
    if ((base_addr & 0xFF00) != (addr & 0xFF00))
        self->cycles++;
    
    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

void lda_absolute_y(instruction_t* self, cpu_t* cpu) {
    cpu->pc++; // skip opcode

    // because 6502 is little endian, we get low byte first
    uint16_t base_addr = read16(cpu, cpu->pc++);
    cpu->pc++; // increment one more time as we are reading 2 bytes
    uint16_t addr = base_addr + cpu->y;
    
    // checking if the page boundary is crossed
    if ((base_addr & 0xFF00) != (addr & 0xFF00))
        self->cycles++;

    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

void lda_indirect_x(instruction_t* self, cpu_t* cpu) {
    (void)self;
    cpu->pc++; // skip opcode
    
    uint8_t base_addr = read8(cpu, cpu->pc++);
    uint8_t indirect_addr = base_addr + cpu->x;
    uint8_t addr = read8(cpu, indirect_addr);
    
    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

void lda_indirect_y(instruction_t* self, cpu_t* cpu) {
    cpu->pc++; // skip opcode

    uint8_t indirect_addr = read8(cpu, cpu->pc++);
    uint8_t base_addr = read8(cpu, indirect_addr);
    uint8_t addr = base_addr + cpu->y;

    // checking if the page boundary is crossed
    if ((base_addr & 0xFF00) != (addr & 0xFF00))
        self->cycles++;

    cpu->a = read8(cpu, addr);

    lda_update_status(cpu);
}

