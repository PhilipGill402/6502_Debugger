#include "instructions/functions.h"
#include "helpers.h"

#include <stdio.h>

void adc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    uint8_t carry = (cpu->status & CARRY) ? 1 : 0;
    
    uint8_t pre_add = cpu->a;
    uint16_t sum = cpu->a + value + carry;
    uint8_t result = (uint8_t)sum;

    cpu->a = result;
    
    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, cpu->a & (1 << 7));
    set_flag(cpu, CARRY, sum > 0xFF);     
    set_flag(cpu, OVERFLOW, (~(pre_add ^ value) & (pre_add ^ result) & (1 << 7)) != 0); 
}

void and(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    cpu->a = cpu->a & value;

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, cpu->a & (1 << 7));
}

void asl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value;
    uint16_t addr;

    if (mode == ADDRESS_ACCUMULATOR) {
        value = cpu->a;
    } else {
        addr = get_effective_address(cpu, mode);
        value = read8(cpu, addr);
    }
    
    uint8_t new_value = value << 1;
    uint8_t carry = (value & CARRY) ? 1 : 0;

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = new_value;
    else
        write8(cpu, addr, new_value);

    set_flag(cpu, CARRY, carry); 
    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, new_value & (1 << 7));
}

void bcc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // carry is not clear
    if (test_flag(cpu, CARRY))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void bcs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // carry is clear
    if (!test_flag(cpu, CARRY))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void beq(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // zero is not clear
    if (test_flag(cpu, ZERO))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void bit(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    uint8_t result = cpu->a & value;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, OVERFLOW, result & (1 << 6) != 0); // sets the overflow flag to bit 6 of the result
    set_flag(cpu, NEGATIVE, result & (1 << 7) != 0); // sets the negative flag to bit 7 of the result
}

void bmi(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // negative is clear
    if (!test_flag(cpu, NEGATIVE))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void bne(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // zero is not clear
    if (test_flag(cpu, ZERO))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void bpl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // negative is not clear
    if (test_flag(cpu, NEGATIVE))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void brk(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    set_flag(cpu, BREAK, 1); 

    push8(cpu, cpu->pc);
    push8(cpu, cpu->status);

    cpu->pc = read16(cpu, INTERRUPT_VECTOR);
}

void bvc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // overflow is not clear
    if (test_flag(cpu, OVERFLOW))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void bvs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // overflow is clear
    if (!test_flag(cpu, OVERFLOW))
        return;

    uint8_t offset = get_value(cpu, mode);
    cpu->pc += offset;
}

void clc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, CARRY, 0);
}

void cld(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, DECIMAL, 0);
}
void cli(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, INTERRUPT, 0);
}

void clv(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, OVERFLOW, 0);
}

void cmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value = get_value(cpu, mode);

    set_flag(cpu, CARRY, cpu->a >= value);
    set_flag(cpu, ZERO, cpu->a == value);
    set_flag(cpu, NEGATIVE, (cpu->a - value) & (1 << 7) != 0);
}

void cpx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value = get_value(cpu, mode);

    set_flag(cpu, CARRY, cpu->x >= value);
    set_flag(cpu, ZERO, cpu->x == value);
    set_flag(cpu, NEGATIVE, (cpu->x - value) & (1 << 7) != 0);
}

void cpy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value = get_value(cpu, mode);

    set_flag(cpu, CARRY, cpu->y >= value);
    set_flag(cpu, ZERO, cpu->y == value);
    set_flag(cpu, NEGATIVE, (cpu->y - value) & (1 << 7) != 0);
}

void dec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t result = read8(cpu, addr) - 1;
    write8(cpu, addr, result);

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & (1 << 7) != 0);
}

void dex(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x--;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, cpu->x & (1 << 7) != 0);
}

void dey(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->y--;

    set_flag(cpu, ZERO, cpu->y == 0);
    set_flag(cpu, NEGATIVE, cpu->y & (1 << 7) != 0);
}

void eor(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t value;

    if (mode == ADDRESS_IMMEDIATE)
        value = read8(cpu, cpu->pc++);
    else
        value = read8(cpu, addr);

    uint8_t result = cpu->a ^ value;
    cpu->a = result;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & (1 << 7) != 0);
}

void inc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t result = read8(cpu, addr) + 1;
    write8(cpu, addr, result);

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & (1 << 7) != 0);
}

void inx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x++;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, cpu->x & (1 << 7) != 0);
}

void iny(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->y++;

    set_flag(cpu, ZERO, cpu->y == 0);
    set_flag(cpu, NEGATIVE, cpu->y & (1 << 7) != 0);
}

void jmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->pc = get_effective_address(cpu, mode);
}

void jsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    push16(cpu->pc);

    cpu->pc = get_effective_address(cpu, mode);
}

void lda(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    cpu->a = get_value(cpu, mode);

    set_flag(cpu, ZERO, cpu->a == 0); 
    set_flag(cpu, NEGATIVE, cpu->a & (1 << 7));
}

void ldx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    cpu->x = get_value(cpu, mode);

    set_flag(cpu, ZERO, cpu->x == 0); 
    set_flag(cpu, NEGATIVE, cpu->x & (1 << 7));
}

void ldy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x = get_value(cpu, mode);

    set_flag(cpu, ZERO, cpu->y == 0); 
    set_flag(cpu, NEGATIVE, cpu->y & (1 << 7));
}

void lsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t preshift = read8(cpu, addr);
    uint8_t postshift = preshift >> 1;

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = postshift;
    else
        write8(cpu, addr, postshift);
    
    set_flag(cpu, CARRY, preshift & 0x0001);
    set_flag(cpu, ZERO, !postshift);
    set_flag(cpu, NEGATIVE, postshift & (1 << 7));    
}

void nop(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    (void)mode;

    cpu->pc++;
}

void ora(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    cpu->a = cpu->a | value;

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, cpu->a & (1 << 7));
}

void pha(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    push8(cpu, cpu->a);
}

void php(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    push8(cpu, cpu->status);
}

void pla(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->a = pull8(cpu);

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, cpu->a & (1 << 7) != 0);
}

void plp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->status = pull8(cpu);

    set_flag(cpu, ZERO, cpu->status == 0);
    set_flag(cpu, NEGATIVE, cpu->status & (1 << 7) != 0);
}

void rol(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void ror(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void rti(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void rts(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void sbc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void sec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void sed(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void sei(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void sta(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void stx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void sty(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void tax(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void tay(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void tsx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void txa(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void txs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void tya(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

