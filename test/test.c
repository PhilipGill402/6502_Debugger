#include "test.h"
#include "../include/instructions/addressing_modes.h"
#include "../include/instructions/instruction_def.h"
#include "../include/instructions/instructions.h"
#include "../include/cpu.h"
#include "../include/helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void write_instruction(cpu_t* cpu, uint8_t opcode, uint8_t arg1, int16_t arg2) {
    write8(cpu, cpu->pc, opcode); // write the opcode
    
    // we only want to write 1 byte if there is only one byte of arguments
    if (arg2 < 0)
        write8(cpu, cpu->pc+1, arg1);
    else
        write16(cpu, cpu->pc+1, ((uint16_t)arg2 << 8) | arg1);
}

static void test_instruction(cpu_t* cpu, uint8_t opcode, uint8_t arg1, int16_t arg2) {
    write_instruction(cpu, opcode, arg1, arg2);
    instruction_t ins = instruction_init(cpu->mem[cpu->pc]);
    ins.execute(&ins, cpu, ins.mode);
}

static void reset_test_cpu(cpu_t* cpu) {
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;
    cpu->pc = 0x8000;
    cpu->sp = 0xFF;
    cpu->status = 0;

    memset(cpu->mem, 0, MEM_SIZE);
}

/* ADC */

static void test_adc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x10;
    set_flag(cpu, CARRY, false);

    test_instruction(cpu, ADC_IMMEDIATE, 0x20, -1);

    assert(cpu->a == 0x30);
    assert(!test_flag(cpu, CARRY));
    assert(!test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, OVERFLOW));

    reset_test_cpu(cpu);

    cpu->a = 0xFF;
    set_flag(cpu, CARRY, false);

    test_instruction(cpu, ADC_IMMEDIATE, 0x01, -1);

    assert(cpu->a == 0x00);
    assert(test_flag(cpu, CARRY));
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, OVERFLOW));

    reset_test_cpu(cpu);

    cpu->a = 0x7F;
    set_flag(cpu, CARRY, false);

    test_instruction(cpu, ADC_IMMEDIATE, 0x01, -1);

    assert(cpu->a == 0x80);
    assert(!test_flag(cpu, CARRY));
    assert(!test_flag(cpu, ZERO));
    assert(test_flag(cpu, NEGATIVE));
    assert(test_flag(cpu, OVERFLOW));
}

/* AND */

static void test_and(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0xF0;

    test_instruction(cpu, AND_IMMEDIATE, 0x0F, -1);

    assert(cpu->a == 0x00);
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));

    reset_test_cpu(cpu);

    cpu->a = 0xFF;

    test_instruction(cpu, AND_IMMEDIATE, 0x80, -1);

    assert(cpu->a == 0x80);
    assert(!test_flag(cpu, ZERO));
    assert(test_flag(cpu, NEGATIVE));
}

/* ASL */

static void test_asl(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x81;

    test_instruction(cpu, ASL_ACCUMULATOR, 0, -1);

    assert(cpu->a == 0x02);
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));

    reset_test_cpu(cpu);

    write8(cpu, 0x42, 0x40);

    test_instruction(cpu, ASL_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x80);
    assert(!test_flag(cpu, CARRY));
    assert(!test_flag(cpu, ZERO));
    assert(test_flag(cpu, NEGATIVE));
}

/* Branches */

static void test_bcc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, CARRY, false);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BCC_RELATIVE, 0x05, -1);
    
    assert(cpu->pc == (start + 2 + 5));

    reset_test_cpu(cpu);

    set_flag(cpu, CARRY, true);

    start = cpu->pc;
    
    test_instruction(cpu, BCC_RELATIVE, 0x05, -1);
    assert(cpu->pc == start + 2);
}

static void test_bcs(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, CARRY, true);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BCS_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

static void test_beq(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, ZERO, true);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BEQ_RELATIVE, 0x05, -1);
    assert(cpu->pc == start + 2 + 5);
}

static void test_bmi(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, NEGATIVE, true);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BMI_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

static void test_bne(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, ZERO, false);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BNE_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

static void test_bpl(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, NEGATIVE, false);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BPL_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

static void test_bvc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, OVERFLOW, false);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BVC_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

static void test_bvs(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, OVERFLOW, true);

    uint16_t start = cpu->pc;

    test_instruction(cpu, BVS_RELATIVE, 0x05, -1);

    assert(cpu->pc == start + 2 + 5);
}

/* BIT */

static void test_bit(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x0F;
    write8(cpu, 0x42, 0xC0);

    test_instruction(cpu, BIT_ZERO_PAGE, 0x42, -1);

    assert(test_flag(cpu, ZERO));
    assert(test_flag(cpu, NEGATIVE));
    assert(test_flag(cpu, OVERFLOW));
}

/* BRK */

static void test_brk(cpu_t* cpu) {
    reset_test_cpu(cpu);

    write16(cpu, 0xFFFE, 0x9000);

    uint8_t old_sp = cpu->sp;

    test_instruction(cpu, BRK_IMPLIED, 0, -1);
    assert(cpu->pc == 0x9000);
    assert(cpu->sp == (uint8_t)(old_sp - 3));
}

/* Clear flags */

static void test_clc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, CARRY, true);

    test_instruction(cpu, CLC_IMPLIED, 0, -1);

    assert(!test_flag(cpu, CARRY));
}

static void test_cld(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, DECIMAL, true);

    test_instruction(cpu, CLD_IMPLIED, 0, -1);

    assert(!test_flag(cpu, DECIMAL));
}

static void test_cli(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, INTERRUPT, true);

    test_instruction(cpu, CLI_IMPLIED, 0, -1);

    assert(!test_flag(cpu, INTERRUPT));
}

static void test_clv(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, OVERFLOW, true);

    test_instruction(cpu, CLV_IMPLIED, 0, -1);

    assert(!test_flag(cpu, OVERFLOW));
}

/* CMP */

static void test_cmp(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x50;

    test_instruction(cpu, CMP_IMMEDIATE, 0x50, -1);

    assert(test_flag(cpu, ZERO));
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, NEGATIVE));

    reset_test_cpu(cpu);

    cpu->a = 0x20;

    test_instruction(cpu, CMP_IMMEDIATE, 0x30, -1);

    assert(!test_flag(cpu, ZERO));
    assert(!test_flag(cpu, CARRY));
    assert(test_flag(cpu, NEGATIVE));
}

/* CPX */

static void test_cpx(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0x50;

    test_instruction(cpu, CPX_IMMEDIATE, 0x50, -1);

    assert(test_flag(cpu, ZERO));
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, NEGATIVE));
}

/* CPY */

static void test_cpy(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->y = 0x50;

    test_instruction(cpu, CPY_IMMEDIATE, 0x50, -1);

    assert(test_flag(cpu, ZERO));
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, NEGATIVE));
}

/* DEC / DEX / DEY */

static void test_dec(cpu_t* cpu) {
    reset_test_cpu(cpu);

    write8(cpu, 0x42, 0x01);

    test_instruction(cpu, DEC_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x00);
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

static void test_dex(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0x01;

    test_instruction(cpu, DEX_IMPLIED, 0, -1);

    assert(cpu->x == 0x00);
    assert(test_flag(cpu, ZERO));
}

static void test_dey(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->y = 0x00;

    test_instruction(cpu, DEY_IMPLIED, 0, -1);

    assert(cpu->y == 0xFF);
    assert(test_flag(cpu, NEGATIVE));
}

/* EOR */

static void test_eor(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0xFF;

    test_instruction(cpu, EOR_IMMEDIATE, 0x0F, -1);

    assert(cpu->a == 0xF0);
    assert(test_flag(cpu, NEGATIVE));
}

/* INC / INX / INY */

static void test_inc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    write8(cpu, 0x42, 0xFF);

    test_instruction(cpu, INC_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x00);
    assert(test_flag(cpu, ZERO));
}

static void test_inx(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0xFF;

    test_instruction(cpu, INX_IMPLIED, 0, -1);

    assert(cpu->x == 0x00);
    assert(test_flag(cpu, ZERO));
}

static void test_iny(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->y = 0x7F;

    test_instruction(cpu, INY_IMPLIED, 0, -1);

    assert(cpu->y == 0x80);
    assert(test_flag(cpu, NEGATIVE));
}

/* JMP */

static void test_jmp(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, JMP_ABSOLUTE, 0x34, 0x12);

    assert(cpu->pc == 0x1234);
}

/* JSR */

static void test_jsr(cpu_t* cpu) {
    reset_test_cpu(cpu);

    uint16_t start = cpu->pc;
    uint8_t old_sp = cpu->sp;

    test_instruction(cpu, JSR_ABSOLUTE, 0x34, 0x12);

    assert(cpu->pc == 0x1234);
    assert(cpu->sp == (uint8_t)(old_sp - 2));
    
    uint16_t ret = pull16(cpu);
    
    assert(ret == start + 2);
}

/* LDA */

static void test_lda(cpu_t* cpu) {
    reset_test_cpu(cpu);

    // immediate
    test_instruction(cpu, LDA_IMMEDIATE, 0x99, -1);
    assert(cpu->a == 0x99);
    assert(test_flag(cpu, NEGATIVE));

    reset_test_cpu(cpu);

    // zero page
    write8(cpu, 0x99, 0x67);
    test_instruction(cpu, LDA_ZERO_PAGE, 0x99, -1);
    assert(cpu->a == 0x67);

    reset_test_cpu(cpu);

    // zero page X
    cpu->x = 0x67;
    write8(cpu, (uint8_t)(0x99 + cpu->x), 0x69);

    test_instruction(cpu, LDA_ZERO_PAGE_X, 0x99, -1);

    assert(cpu->a == 0x69);

    reset_test_cpu(cpu);

    // absolute
    write8(cpu, 0x6967, 0x99);

    test_instruction(cpu, LDA_ABSOLUTE, 0x67, 0x69);

    assert(cpu->a == 0x99);

    reset_test_cpu(cpu);

    // absolute X
    cpu->x = 0xFF;
    write8(cpu, (uint16_t)(0x6967 + cpu->x), 0x99);

    test_instruction(cpu, LDA_ABSOLUTE_X, 0x67, 0x69);

    assert(cpu->a == 0x99);

    reset_test_cpu(cpu);

    // absolute Y
    cpu->y = 0x01;
    write8(cpu, (uint16_t)(0x6967 + cpu->y), 0x99);

    test_instruction(cpu, LDA_ABSOLUTE_Y, 0x67, 0x69);

    assert(cpu->a == 0x99);

    reset_test_cpu(cpu);

    // indexed indirect
    cpu->x = 0x67;

    write8(cpu, 0x66, 0x99);
    write8(cpu, 0x67, 0xFF);
    write8(cpu, 0xFF99, 0x67);

    test_instruction(cpu, LDA_INDEXED_INDIRECT, 0xFF, -1);

    assert(cpu->a == 0x67);

    reset_test_cpu(cpu);

    // indirect indexed
    cpu->y = 0xFF;

    write8(cpu, 0x69, 0x67);
    write8(cpu, 0x6A, 0xFF);
    write8(cpu, (uint16_t)(0xFF67 + cpu->y), 0x99);

    test_instruction(cpu, LDA_INDIRECT_INDEXED, 0x69, -1);

    assert(cpu->a == 0x99);

    reset_test_cpu(cpu);

    // zero flag
    test_instruction(cpu, LDA_IMMEDIATE, 0x00, -1);

    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

/* LDX */

static void test_ldx(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, LDX_IMMEDIATE, 0x80, -1);

    assert(cpu->x == 0x80);
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* LDY */

static void test_ldy(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, LDY_IMMEDIATE, 0x00, -1);

    assert(cpu->y == 0x00);
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

/* LSR */

static void test_lsr(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x01;

    test_instruction(cpu, LSR_ACCUMULATOR, 0, -1);

    assert(cpu->a == 0x00);
    assert(test_flag(cpu, CARRY));
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

/* NOP */

static void test_nop(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x12;
    cpu->x = 0x34;
    cpu->y = 0x56;
    cpu->status = CARRY | NEGATIVE;

    uint8_t a = cpu->a;
    uint8_t x = cpu->x;
    uint8_t y = cpu->y;
    uint8_t status = cpu->status;

    test_instruction(cpu, NOP_IMPLIED, 0, -1);

    assert(cpu->a == a);
    assert(cpu->x == x);
    assert(cpu->y == y);
    assert(cpu->status == status);
}

/* ORA */

static void test_ora(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x80;

    test_instruction(cpu, ORA_IMMEDIATE, 0x01, -1);

    assert(cpu->a == 0x81);
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* PHA */

static void test_pha(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x69;
    uint8_t old_sp = cpu->sp;

    test_instruction(cpu, PHA_IMPLIED, 0, -1);

    assert(cpu->sp == (uint8_t)(old_sp - 1));
    assert(pull8(cpu) == 0x69);
}

/* PHP */

static void test_php(cpu_t* cpu) {
    reset_test_cpu(cpu);

    set_flag(cpu, CARRY, true);
    set_flag(cpu, ZERO, true);

    test_instruction(cpu, PHP_IMPLIED, 0, -1);

    uint8_t status = pull8(cpu);

    assert(status & CARRY);
    assert(status & ZERO);
}

/* PLA */

static void test_pla(cpu_t* cpu) {
    reset_test_cpu(cpu);

    push8(cpu, 0x80);

    test_instruction(cpu, PLA_IMPLIED, 0, -1);

    assert(cpu->a == 0x80);
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* PLP */

static void test_plp(cpu_t* cpu) {
    reset_test_cpu(cpu);

    push8(cpu, CARRY | ZERO);

    test_instruction(cpu, PLP_IMPLIED, 0, -1);

    assert(test_flag(cpu, CARRY));
    assert(test_flag(cpu, ZERO));
}

/* ROL */

static void test_rol(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x80;
    set_flag(cpu, CARRY, true);

    test_instruction(cpu, ROL_ACCUMULATOR, 0, -1);
    
    assert(cpu->a == 0x01);
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* ROR */

static void test_ror(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x01;
    set_flag(cpu, CARRY, true);

    test_instruction(cpu, ROR_ACCUMULATOR, 0, -1);

    assert(cpu->a == 0x80);
    assert(test_flag(cpu, CARRY));
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* RTI */

static void test_rti(cpu_t* cpu) {
    reset_test_cpu(cpu);

    push16(cpu, 0x1234);
    push8(cpu, CARRY | ZERO);

    test_instruction(cpu, RTI_IMPLIED, 0, -1);

    assert(cpu->pc == 0x1234);
    assert(test_flag(cpu, CARRY));
    assert(test_flag(cpu, ZERO));
}

/* RTS */

static void test_rts(cpu_t* cpu) {
    reset_test_cpu(cpu);
    
    push16(cpu, 0x1234);
    push8(cpu, cpu->status);

    test_instruction(cpu, RTS_IMPLIED, 0, -1);
    
    assert(cpu->pc == 0x1235);
}

/* SBC */

static void test_sbc(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x10;
    set_flag(cpu, CARRY, true);

    test_instruction(cpu, SBC_IMMEDIATE, 0x01, -1);

    assert(cpu->a == 0x0F);
    assert(test_flag(cpu, CARRY));
    assert(!test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));

    reset_test_cpu(cpu);

    cpu->a = 0x00;
    set_flag(cpu, CARRY, true);

    test_instruction(cpu, SBC_IMMEDIATE, 0x01, -1);

    assert(cpu->a == 0xFF);
    assert(!test_flag(cpu, CARRY));
    assert(test_flag(cpu, NEGATIVE));
}

/* SEC */

static void test_sec(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, SEC_IMPLIED, 0, -1);

    assert(test_flag(cpu, CARRY));
}

/* SED */

static void test_sed(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, SED_IMPLIED, 0, -1);

    assert(test_flag(cpu, DECIMAL));
}

/* SEI */

static void test_sei(cpu_t* cpu) {
    reset_test_cpu(cpu);

    test_instruction(cpu, SEI_IMPLIED, 0, -1);

    assert(test_flag(cpu, INTERRUPT));
}

/* STA */

static void test_sta(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x69;

    test_instruction(cpu, STA_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x69);
}

/* STX */

static void test_stx(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0x69;

    test_instruction(cpu, STX_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x69);
}

/* STY */

static void test_sty(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->y = 0x69;

    test_instruction(cpu, STY_ZERO_PAGE, 0x42, -1);

    assert(read8(cpu, 0x42) == 0x69);
}

/* TAX */

static void test_tax(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x80;

    test_instruction(cpu, TAX_IMPLIED, 0, -1);

    assert(cpu->x == 0x80);
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

/* TAY */

static void test_tay(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->a = 0x00;

    test_instruction(cpu, TAY_IMPLIED, 0, -1);

    assert(cpu->y == 0x00);
    assert(test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

/* TSX */

static void test_tsx(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->sp = 0x80;

    test_instruction(cpu, TSX_IMPLIED, 0, -1);

    assert(cpu->x == 0x80);
    assert(test_flag(cpu, NEGATIVE));
}

/* TXA */

static void test_txa(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0x69;

    test_instruction(cpu, TXA_IMPLIED, 0, -1);

    assert(cpu->a == 0x69);
    assert(!test_flag(cpu, ZERO));
    assert(!test_flag(cpu, NEGATIVE));
}

/* TXS */

static void test_txs(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->x = 0x69;
    cpu->status = CARRY | NEGATIVE;

    uint8_t old_status = cpu->status;

    test_instruction(cpu, TXS_IMPLIED, 0, -1);

    assert(cpu->sp == 0x69);
    assert(cpu->status == old_status);
}

/* TYA */

static void test_tya(cpu_t* cpu) {
    reset_test_cpu(cpu);

    cpu->y = 0x80;

    test_instruction(cpu, TYA_IMPLIED, 0, -1);

    assert(cpu->a == 0x80);
    assert(test_flag(cpu, NEGATIVE));
    assert(!test_flag(cpu, ZERO));
}

static void run_instruction_tests(cpu_t* cpu) {
    test_adc(cpu);
    test_and(cpu);
    test_asl(cpu);

    test_bcc(cpu);
    test_bcs(cpu);
    test_beq(cpu);
    test_bit(cpu);
    test_bmi(cpu);
    test_bne(cpu);
    test_bpl(cpu);
    test_brk(cpu);
    test_bvc(cpu);
    test_bvs(cpu);

    test_clc(cpu);
    test_cld(cpu);
    test_cli(cpu);
    test_clv(cpu);
    test_cmp(cpu);
    test_cpx(cpu);
    test_cpy(cpu);

    test_dec(cpu);
    test_dex(cpu);
    test_dey(cpu);

    test_eor(cpu);

    test_inc(cpu);
    test_inx(cpu);
    test_iny(cpu);

    test_jmp(cpu);
    test_jsr(cpu);

    test_lda(cpu);
    test_ldx(cpu);
    test_ldy(cpu);
    test_lsr(cpu);

    test_nop(cpu);
    test_ora(cpu);

    test_pha(cpu);
    test_php(cpu);
    test_pla(cpu);
    test_plp(cpu);

    test_rol(cpu);
    test_ror(cpu);
    test_rti(cpu);
    test_rts(cpu);

    test_sbc(cpu);
    test_sec(cpu);
    test_sed(cpu);
    test_sei(cpu);
    test_sta(cpu);
    test_stx(cpu);
    test_sty(cpu);

    test_tax(cpu);
    test_tay(cpu);
    test_tsx(cpu);
    test_txa(cpu);
    test_txs(cpu);
    test_tya(cpu);
}

void test() {
    cpu_t cpu = cpu_init();
    if (cpu.mem == NULL)
        return;
    
    // hard coding reset vectors
    write8(&cpu, 0xFFFC, 0x80);
    write8(&cpu, 0xFFFD, 0x00);

    cpu_reset(&cpu);

    run_instruction_tests(&cpu);        

    cpu_free(&cpu);
    return;
}
