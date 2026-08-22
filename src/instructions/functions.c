#include "instructions/functions.h"
#include "helpers.h"

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
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
    set_flag(cpu, CARRY, sum > 0xFF);     
    set_flag(cpu, OVERFLOW, (~(pre_add ^ value) & (pre_add ^ result) & (1 << 7)) != 0); 
}

void and(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    cpu->a = cpu->a & value;

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
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
    
    uint8_t carry = ((value & (1 << 7)) != 0);

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = new_value;
    else
        write8(cpu, addr, new_value);
    
    set_flag(cpu, CARRY, carry); 
    set_flag(cpu, ZERO, new_value == 0);
    set_flag(cpu, NEGATIVE, (new_value & (1 << 7)) != 0);
}

void bcc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // carry is not clear
    if (test_flag(cpu, CARRY)) {
        cpu->pc++;
        return;
    }
    
    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void bcs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // carry is clear
    if (!test_flag(cpu, CARRY)) {
        cpu->pc++;
        return;
    }

    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void beq(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // zero is clear 
    if (!test_flag(cpu, ZERO)) {
        cpu->pc++;
        return;
    }
    
    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void bit(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    uint8_t result = cpu->a & value;
    
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, OVERFLOW, (value & (1 << 6)) != 0); // sets the overflow flag to bit 6 of the result
    set_flag(cpu, NEGATIVE, (value & (1 << 7)) != 0); // sets the negative flag to bit 7 of the result
}

void bmi(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // negative is clear
    if (!test_flag(cpu, NEGATIVE))
        return;

    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void bne(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // zero is not clear
    if (test_flag(cpu, ZERO))
        return;

    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void bpl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // negative is not clear
    if (test_flag(cpu, NEGATIVE))
        return;

    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void brk(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    set_flag(cpu, BREAK, 1); 

    push16(cpu, cpu->pc);
    push8(cpu, cpu->status);

    cpu->pc = read16(cpu, INTERRUPT_VECTOR);
}

void bvc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // overflow is not clear
    if (test_flag(cpu, OVERFLOW))
        return;

    int8_t offset = (int8_t)get_value(cpu, mode);
    cpu->pc += offset;
}

void bvs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    // overflow is clear
    if (!test_flag(cpu, OVERFLOW))
        return;

    int8_t offset = (int8_t)get_value(cpu, mode);
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
    set_flag(cpu, NEGATIVE, ((cpu->a - value) & (1 << 7)) != 0);
}

void cpx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value = get_value(cpu, mode);

    set_flag(cpu, CARRY, cpu->x >= value);
    set_flag(cpu, ZERO, cpu->x == value);
    set_flag(cpu, NEGATIVE, ((cpu->x - value) & (1 << 7)) != 0);
}

void cpy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint8_t value = get_value(cpu, mode);

    set_flag(cpu, CARRY, cpu->y >= value);
    set_flag(cpu, ZERO, cpu->y == value);
    set_flag(cpu, NEGATIVE, ((cpu->y - value) & (1 << 7)) != 0);
}

void dec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t result = read8(cpu, addr) - 1;
    write8(cpu, addr, result);

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, (result & (1 << 7)) != 0);
}

void dex(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x--;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, (cpu->x & (1 << 7)) != 0);
}

void dey(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->y--;

    set_flag(cpu, ZERO, cpu->y == 0);
    set_flag(cpu, NEGATIVE, (cpu->y & (1 << 7)) != 0);
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
    set_flag(cpu, NEGATIVE, (result & (1 << 7)) != 0);
}

void inc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t result = read8(cpu, addr) + 1;
    write8(cpu, addr, result);

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, (result & (1 << 7)) != 0);
}

void inx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x++;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, (cpu->x & (1 << 7)) != 0);
}

void iny(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->y++;

    set_flag(cpu, ZERO, cpu->y == 0);
    set_flag(cpu, NEGATIVE, (cpu->y & (1 << 7)) != 0);
}

void jmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->pc = get_effective_address(cpu, mode);
}

void jsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    uint16_t addr = get_effective_address(cpu, mode);
    push16(cpu, cpu->pc - 1);

    cpu->pc = addr;
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
    uint8_t preshift;
    if (mode == ADDRESS_ACCUMULATOR)
        preshift = cpu->a;
    else
        preshift = read8(cpu, addr);
    
    uint8_t postshift = preshift >> 1;

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = postshift;
    else
        write8(cpu, addr, postshift);
    
    set_flag(cpu, CARRY, (preshift & (1 << 0)) != 0);
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
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
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
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
}

void plp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->status = pull8(cpu);
}

void rol(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t value;

    if (mode == ADDRESS_ACCUMULATOR)
        value = cpu->a;
    else
        value = read8(cpu, addr);

    uint8_t result = value << 1;
    if (test_flag(cpu, CARRY))
        result |= 1;
    else
        result &= 0;

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = result;
    else
        write8(cpu, addr, result);

    set_flag(cpu, CARRY, (value & (1 << 7)) != 0);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, (result & (1 << 7)) != 0);
}

void ror(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint16_t addr = get_effective_address(cpu, mode);
    uint8_t value;

    if (mode == ADDRESS_ACCUMULATOR)
        value = cpu->a;
    else
        value = read8(cpu, addr);

    uint8_t result = value >> 1;
    if (test_flag(cpu, CARRY))
        result |= 1 << 7;
    else
        result &= 1 << 7;

    if (mode == ADDRESS_ACCUMULATOR)
        cpu->a = result;
    else
        write8(cpu, addr, result);

    set_flag(cpu, CARRY, (value & (1 << 0)) != 0);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, (result & (1 << 7)) != 0);
}

void rti(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t status = pull8(cpu);
    uint16_t pc = pull16(cpu);

    cpu->status = status;
    cpu->pc = pc;
}

void rts(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t status = pull8(cpu);
    uint16_t pc = pull16(cpu);

    cpu->status = status;
    cpu->pc = pc + 1;
}

void sbc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint8_t value = get_value(cpu, mode);
    uint8_t borrow = test_flag(cpu, CARRY) ? 0: 1;
    
    uint8_t pre_sub = cpu->a;
    uint16_t diff = (uint16_t)cpu->a - value - borrow;
    uint8_t result = (uint8_t)diff;

    cpu->a = result;
    
    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
    set_flag(cpu, CARRY, pre_sub >= value + borrow);     
    set_flag(cpu, OVERFLOW, ((pre_sub ^ result) & (pre_sub ^ value) & (1 << 7)) != 0);
}

void sec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, CARRY, 1);
}

void sed(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, DECIMAL, 1);
}

void sei(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    set_flag(cpu, INTERRUPT, 1);
}

void sta(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint16_t addr = get_effective_address(cpu, mode);
    write8(cpu, addr, cpu->a);
}

void stx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint16_t addr = get_effective_address(cpu, mode);
    write8(cpu, addr, cpu->x);
}

void sty(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    uint16_t addr = get_effective_address(cpu, mode);
    write8(cpu, addr, cpu->y);
}

void tax(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x = cpu->a;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, (cpu->x & (1 << 7)) != 0);
}

void tay(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->y = cpu->a;

    set_flag(cpu, ZERO, cpu->y == 0);
    set_flag(cpu, NEGATIVE, (cpu->y & (1 << 7)) != 0);
}

void tsx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x = cpu->sp;

    set_flag(cpu, ZERO, cpu->x == 0);
    set_flag(cpu, NEGATIVE, (cpu->x & (1 << 7)) != 0);
}

void txa(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->a = cpu->x;

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
}

void txs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->sp = cpu->x;
}

void tya(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->a = cpu->y;

    set_flag(cpu, ZERO, cpu->a == 0);
    set_flag(cpu, NEGATIVE, (cpu->a & (1 << 7)) != 0);
}

