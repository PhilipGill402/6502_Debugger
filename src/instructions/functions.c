#include "instructions/functions.h"
#include "helpers.h"

#include <stdio.h>

void adc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void and(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void asl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void bcc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bcs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void beq(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bit(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bmi(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bne(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bpl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void brk(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bvc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void bvs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void clc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void cld(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void cli(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void clv(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void cmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void cpx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void cpy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void dec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void dex(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void dey(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void eor(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void inc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void inx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void iny(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void jmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void jsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void lda(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    cpu->a = get_value(cpu, mode);

    if (cpu->a == 0)
        SET_ZERO(cpu->status);

    if (cpu->a & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void ldx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    cpu->x = get_value(cpu, mode);

    if (cpu->x == 0)
        SET_ZERO(cpu->status);

    if (cpu->x & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void ldy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;

    cpu->x = get_value(cpu, mode);

    if (cpu->y == 0)
        SET_ZERO(cpu->status);

    if (cpu->y & (1 << 7))
        SET_NEGATIVE(cpu->status);
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

    if (preshift & 0x0001)
        SET_CARRY(cpu->status);
    else
        CLEAR_CARRY(cpu->status);
    
    if (!postshift)
        SET_ZERO(cpu->status);

    if (postshift & (1 << 7))
        SET_NEGATIVE(cpu->status);
}

void nop(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void ora(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

void pha(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void php(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void pla(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}
void plp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {}

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

