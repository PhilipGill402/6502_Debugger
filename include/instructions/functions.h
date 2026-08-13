#ifndef INCLUDE_INSTRUCTIONS_FUNCTIONS_H_
#define INCLUDE_INSTRUCTIONS_FUNCTIONS_H_

#include "instructions/instruction_def.h"
#include "instructions/addressing_modes.h"
#include "cpu.h"

void adc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void and(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void asl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void bcc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bcs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void beq(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bit(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bmi(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bne(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bpl(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void brk(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bvc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void bvs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void clc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void cld(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void cli(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void clv(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void cmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void cpx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void cpy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void dec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void dex(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void dey(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void eor(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void inc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void inx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void iny(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void jmp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void jsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void lda(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void ldx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void ldy(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void lsr(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void nop(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void ora(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void pha(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void php(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void pla(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void plp(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void rol(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void ror(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void rti(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void rts(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void sbc(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void sec(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void sed(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void sei(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void sta(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void stx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void sty(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

void tax(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void tay(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void tsx(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void txa(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void txs(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);
void tya(instruction_t* self, cpu_t* cpu, addressing_mode_t mode);

#endif
