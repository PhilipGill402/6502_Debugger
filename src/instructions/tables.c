#include "instructions/tables.h"
#include "instructions/functions.h"

instruction_fn instruction_table[256] = {
    /* 0x00 */
    [0x00] = brk,
    [0x01] = ora,
    [0x05] = ora,
    [0x06] = asl,
    [0x08] = php,
    [0x09] = ora,
    [0x0A] = asl,
    [0x0D] = ora,
    [0x0E] = asl,

    /* 0x10 */
    [0x10] = bpl,
    [0x11] = ora,
    [0x15] = ora,
    [0x16] = asl,
    [0x18] = clc,
    [0x19] = ora,
    [0x1D] = ora,
    [0x1E] = asl,

    /* 0x20 */
    [0x20] = jsr,
    [0x21] = and,
    [0x24] = bit,
    [0x25] = and,
    [0x26] = rol,
    [0x28] = plp,
    [0x29] = and,
    [0x2A] = rol,
    [0x2C] = bit,
    [0x2D] = and,
    [0x2E] = rol,

    /* 0x30 */
    [0x30] = bmi,
    [0x31] = and,
    [0x35] = and,
    [0x36] = rol,
    [0x38] = sec,
    [0x39] = and,
    [0x3D] = and,
    [0x3E] = rol,

    /* 0x40 */
    [0x40] = rti,
    [0x41] = eor,
    [0x45] = eor,
    [0x46] = lsr,
    [0x48] = pha,
    [0x49] = eor,
    [0x4A] = lsr,
    [0x4C] = jmp,
    [0x4D] = eor,
    [0x4E] = lsr,

    /* 0x50 */
    [0x50] = bvc,
    [0x51] = eor,
    [0x55] = eor,
    [0x56] = lsr,
    [0x58] = cli,
    [0x59] = eor,
    [0x5D] = eor,
    [0x5E] = lsr,

    /* 0x60 */
    [0x60] = rts,
    [0x61] = adc,
    [0x65] = adc,
    [0x66] = ror,
    [0x68] = pla,
    [0x69] = adc,
    [0x6A] = ror,
    [0x6C] = jmp,
    [0x6D] = adc,
    [0x6E] = ror,

    /* 0x70 */
    [0x70] = bvs,
    [0x71] = adc,
    [0x75] = adc,
    [0x76] = ror,
    [0x78] = sei,
    [0x79] = adc,
    [0x7D] = adc,
    [0x7E] = ror,

    /* 0x80 */
    [0x81] = sta,
    [0x84] = sty,
    [0x85] = sta,
    [0x86] = stx,
    [0x88] = dey,
    [0x8A] = txa,
    [0x8C] = sty,
    [0x8D] = sta,
    [0x8E] = stx,

    /* 0x90 */
    [0x90] = bcc,
    [0x91] = sta,
    [0x94] = sty,
    [0x95] = sta,
    [0x96] = stx,
    [0x98] = tya,
    [0x99] = sta,
    [0x9A] = txs,
    [0x9D] = sta,

    /* 0xA0 */
    [0xA0] = ldy,
    [0xA1] = lda,
    [0xA2] = ldx,
    [0xA4] = ldy,
    [0xA5] = lda,
    [0xA6] = ldx,
    [0xA8] = tay,
    [0xA9] = lda,
    [0xAA] = tax,
    [0xAC] = ldy,
    [0xAD] = lda,
    [0xAE] = ldx,

    /* 0xB0 */
    [0xB0] = bcs,
    [0xB1] = lda,
    [0xB4] = ldy,
    [0xB5] = lda,
    [0xB6] = ldx,
    [0xB8] = clv,
    [0xB9] = lda,
    [0xBA] = tsx,
    [0xBC] = ldy,
    [0xBD] = lda,
    [0xBE] = ldx,

    /* 0xC0 */
    [0xC0] = cpy,
    [0xC1] = cmp,
    [0xC4] = cpy,
    [0xC5] = cmp,
    [0xC6] = dec,
    [0xC8] = iny,
    [0xC9] = cmp,
    [0xCA] = dex,
    [0xCC] = cpy,
    [0xCD] = cmp,
    [0xCE] = dec,

    /* 0xD0 */
    [0xD0] = bne,
    [0xD1] = cmp,
    [0xD5] = cmp,
    [0xD6] = dec,
    [0xD8] = cld,
    [0xD9] = cmp,
    [0xDD] = cmp,
    [0xDE] = dec,

    /* 0xE0 */
    [0xE0] = cpx,
    [0xE1] = sbc,
    [0xE4] = cpx,
    [0xE5] = sbc,
    [0xE6] = inc,
    [0xE8] = inx,
    [0xE9] = sbc,
    [0xEA] = nop,
    [0xEC] = cpx,
    [0xED] = sbc,
    [0xEE] = inc,

    /* 0xF0 */
    [0xF0] = beq,
    [0xF1] = sbc,
    [0xF5] = sbc,
    [0xF6] = inc,
    [0xF8] = sed,
    [0xF9] = sbc,
    [0xFD] = sbc,
    [0xFE] = inc,
};

uint8_t instruction_cycles[256] = {
    /* 0x00 */
    [0x00] = 7,  // BRK
    [0x01] = 6,  // ORA (indirect,X)
    [0x05] = 3,  // ORA zero page
    [0x06] = 5,  // ASL zero page
    [0x08] = 3,  // PHP
    [0x09] = 2,  // ORA immediate
    [0x0A] = 2,  // ASL accumulator
    [0x0D] = 4,  // ORA absolute
    [0x0E] = 6,  // ASL absolute

    /* 0x10 */
    [0x10] = 2,  // BPL
    [0x11] = 5,  // ORA (indirect),Y
    [0x15] = 4,  // ORA zero page,X
    [0x16] = 6,  // ASL zero page,X
    [0x18] = 2,  // CLC
    [0x19] = 4,  // ORA absolute,Y
    [0x1D] = 4,  // ORA absolute,X
    [0x1E] = 7,  // ASL absolute,X

    /* 0x20 */
    [0x20] = 6,  // JSR
    [0x21] = 6,  // AND (indirect,X)
    [0x24] = 3,  // BIT zero page
    [0x25] = 3,  // AND zero page
    [0x26] = 5,  // ROL zero page
    [0x28] = 4,  // PLP
    [0x29] = 2,  // AND immediate
    [0x2A] = 2,  // ROL accumulator
    [0x2C] = 4,  // BIT absolute
    [0x2D] = 4,  // AND absolute
    [0x2E] = 6,  // ROL absolute

    /* 0x30 */
    [0x30] = 2,  // BMI
    [0x31] = 5,  // AND (indirect),Y
    [0x35] = 4,  // AND zero page,X
    [0x36] = 6,  // ROL zero page,X
    [0x38] = 2,  // SEC
    [0x39] = 4,  // AND absolute,Y
    [0x3D] = 4,  // AND absolute,X
    [0x3E] = 7,  // ROL absolute,X

    /* 0x40 */
    [0x40] = 6,  // RTI
    [0x41] = 6,  // EOR (indirect,X)
    [0x45] = 3,  // EOR zero page
    [0x46] = 5,  // LSR zero page
    [0x48] = 3,  // PHA
    [0x49] = 2,  // EOR immediate
    [0x4A] = 2,  // LSR accumulator
    [0x4C] = 3,  // JMP absolute
    [0x4D] = 4,  // EOR absolute
    [0x4E] = 6,  // LSR absolute

    /* 0x50 */
    [0x50] = 2,  // BVC
    [0x51] = 5,  // EOR (indirect),Y
    [0x55] = 4,  // EOR zero page,X
    [0x56] = 6,  // LSR zero page,X
    [0x58] = 2,  // CLI
    [0x59] = 4,  // EOR absolute,Y
    [0x5D] = 4,  // EOR absolute,X
    [0x5E] = 7,  // LSR absolute,X

    /* 0x60 */
    [0x60] = 6,  // RTS
    [0x61] = 6,  // ADC (indirect,X)
    [0x65] = 3,  // ADC zero page
    [0x66] = 5,  // ROR zero page
    [0x68] = 4,  // PLA
    [0x69] = 2,  // ADC immediate
    [0x6A] = 2,  // ROR accumulator
    [0x6C] = 5,  // JMP indirect
    [0x6D] = 4,  // ADC absolute
    [0x6E] = 6,  // ROR absolute

    /* 0x70 */
    [0x70] = 2,  // BVS
    [0x71] = 5,  // ADC (indirect),Y
    [0x75] = 4,  // ADC zero page,X
    [0x76] = 6,  // ROR zero page,X
    [0x78] = 2,  // SEI
    [0x79] = 4,  // ADC absolute,Y
    [0x7D] = 4,  // ADC absolute,X
    [0x7E] = 7,  // ROR absolute,X

    /* 0x80 */
    [0x81] = 6,  // STA (indirect,X)
    [0x84] = 3,  // STY zero page
    [0x85] = 3,  // STA zero page
    [0x86] = 3,  // STX zero page
    [0x88] = 2,  // DEY
    [0x8A] = 2,  // TXA
    [0x8C] = 4,  // STY absolute
    [0x8D] = 4,  // STA absolute
    [0x8E] = 4,  // STX absolute

    /* 0x90 */
    [0x90] = 2,  // BCC
    [0x91] = 6,  // STA (indirect),Y
    [0x94] = 4,  // STY zero page,X
    [0x95] = 4,  // STA zero page,X
    [0x96] = 4,  // STX zero page,Y
    [0x98] = 2,  // TYA
    [0x99] = 5,  // STA absolute,Y
    [0x9A] = 2,  // TXS
    [0x9D] = 5,  // STA absolute,X

    /* 0xA0 */
    [0xA0] = 2,  // LDY immediate
    [0xA1] = 6,  // LDA (indirect,X)
    [0xA2] = 2,  // LDX immediate
    [0xA4] = 3,  // LDY zero page
    [0xA5] = 3,  // LDA zero page
    [0xA6] = 3,  // LDX zero page
    [0xA8] = 2,  // TAY
    [0xA9] = 2,  // LDA immediate
    [0xAA] = 2,  // TAX
    [0xAC] = 4,  // LDY absolute
    [0xAD] = 4,  // LDA absolute
    [0xAE] = 4,  // LDX absolute

    /* 0xB0 */
    [0xB0] = 2,  // BCS
    [0xB1] = 5,  // LDA (indirect),Y
    [0xB4] = 4,  // LDY zero page,X
    [0xB5] = 4,  // LDA zero page,X
    [0xB6] = 4,  // LDX zero page,Y
    [0xB8] = 2,  // CLV
    [0xB9] = 4,  // LDA absolute,Y
    [0xBA] = 2,  // TSX
    [0xBC] = 4,  // LDY absolute,X
    [0xBD] = 4,  // LDA absolute,X
    [0xBE] = 4,  // LDX absolute,Y

    /* 0xC0 */
    [0xC0] = 2,  // CPY immediate
    [0xC1] = 6,  // CMP (indirect,X)
    [0xC4] = 3,  // CPY zero page
    [0xC5] = 3,  // CMP zero page
    [0xC6] = 5,  // DEC zero page
    [0xC8] = 2,  // INY
    [0xC9] = 2,  // CMP immediate
    [0xCA] = 2,  // DEX
    [0xCC] = 4,  // CPY absolute
    [0xCD] = 4,  // CMP absolute
    [0xCE] = 6,  // DEC absolute

    /* 0xD0 */
    [0xD0] = 2,  // BNE
    [0xD1] = 5,  // CMP (indirect),Y
    [0xD5] = 4,  // CMP zero page,X
    [0xD6] = 6,  // DEC zero page,X
    [0xD8] = 2,  // CLD
    [0xD9] = 4,  // CMP absolute,Y
    [0xDD] = 4,  // CMP absolute,X
    [0xDE] = 7,  // DEC absolute,X

    /* 0xE0 */
    [0xE0] = 2,  // CPX immediate
    [0xE1] = 6,  // SBC (indirect,X)
    [0xE4] = 3,  // CPX zero page
    [0xE5] = 3,  // SBC zero page
    [0xE6] = 5,  // INC zero page
    [0xE8] = 2,  // INX
    [0xE9] = 2,  // SBC immediate
    [0xEA] = 2,  // NOP
    [0xEC] = 4,  // CPX absolute
    [0xED] = 4,  // SBC absolute
    [0xEE] = 6,  // INC absolute

    /* 0xF0 */
    [0xF0] = 2,  // BEQ
    [0xF1] = 5,  // SBC (indirect),Y
    [0xF5] = 4,  // SBC zero page,X
    [0xF6] = 6,  // INC zero page,X
    [0xF8] = 2,  // SED
    [0xF9] = 4,  // SBC absolute,Y
    [0xFD] = 4,  // SBC absolute,X
    [0xFE] = 7,  // INC absolute,X
};

uint8_t instruction_bytes[256] = {
    /* 0x00 */
    [0x00] = 1,  // BRK
    [0x01] = 2,
    [0x05] = 2,
    [0x06] = 2,
    [0x08] = 1,
    [0x09] = 2,
    [0x0A] = 1,
    [0x0D] = 3,
    [0x0E] = 3,

    /* 0x10 */
    [0x10] = 2,
    [0x11] = 2,
    [0x15] = 2,
    [0x16] = 2,
    [0x18] = 1,
    [0x19] = 3,
    [0x1D] = 3,
    [0x1E] = 3,

    /* 0x20 */
    [0x20] = 3,
    [0x21] = 2,
    [0x24] = 2,
    [0x25] = 2,
    [0x26] = 2,
    [0x28] = 1,
    [0x29] = 2,
    [0x2A] = 1,
    [0x2C] = 3,
    [0x2D] = 3,
    [0x2E] = 3,

    /* 0x30 */
    [0x30] = 2,
    [0x31] = 2,
    [0x35] = 2,
    [0x36] = 2,
    [0x38] = 1,
    [0x39] = 3,
    [0x3D] = 3,
    [0x3E] = 3,

    /* 0x40 */
    [0x40] = 1,
    [0x41] = 2,
    [0x45] = 2,
    [0x46] = 2,
    [0x48] = 1,
    [0x49] = 2,
    [0x4A] = 1,
    [0x4C] = 3,
    [0x4D] = 3,
    [0x4E] = 3,

    /* 0x50 */
    [0x50] = 2,
    [0x51] = 2,
    [0x55] = 2,
    [0x56] = 2,
    [0x58] = 1,
    [0x59] = 3,
    [0x5D] = 3,
    [0x5E] = 3,

    /* 0x60 */
    [0x60] = 1,
    [0x61] = 2,
    [0x65] = 2,
    [0x66] = 2,
    [0x68] = 1,
    [0x69] = 2,
    [0x6A] = 1,
    [0x6C] = 3,
    [0x6D] = 3,
    [0x6E] = 3,

    /* 0x70 */
    [0x70] = 2,
    [0x71] = 2,
    [0x75] = 2,
    [0x76] = 2,
    [0x78] = 1,
    [0x79] = 3,
    [0x7D] = 3,
    [0x7E] = 3,

    /* 0x80 */
    [0x81] = 2,
    [0x84] = 2,
    [0x85] = 2,
    [0x86] = 2,
    [0x88] = 1,
    [0x8A] = 1,
    [0x8C] = 3,
    [0x8D] = 3,
    [0x8E] = 3,

    /* 0x90 */
    [0x90] = 2,
    [0x91] = 2,
    [0x94] = 2,
    [0x95] = 2,
    [0x96] = 2,
    [0x98] = 1,
    [0x99] = 3,
    [0x9A] = 1,
    [0x9D] = 3,

    /* 0xA0 */
    [0xA0] = 2,
    [0xA1] = 2,
    [0xA2] = 2,
    [0xA4] = 2,
    [0xA5] = 2,
    [0xA6] = 2,
    [0xA8] = 1,
    [0xA9] = 2,
    [0xAA] = 1,
    [0xAC] = 3,
    [0xAD] = 3,
    [0xAE] = 3,

    /* 0xB0 */
    [0xB0] = 2,
    [0xB1] = 2,
    [0xB4] = 2,
    [0xB5] = 2,
    [0xB6] = 2,
    [0xB8] = 1,
    [0xB9] = 3,
    [0xBA] = 1,
    [0xBC] = 3,
    [0xBD] = 3,
    [0xBE] = 3,

    /* 0xC0 */
    [0xC0] = 2,
    [0xC1] = 2,
    [0xC4] = 2,
    [0xC5] = 2,
    [0xC6] = 2,
    [0xC8] = 1,
    [0xC9] = 2,
    [0xCA] = 1,
    [0xCC] = 3,
    [0xCD] = 3,
    [0xCE] = 3,

    /* 0xD0 */
    [0xD0] = 2,
    [0xD1] = 2,
    [0xD5] = 2,
    [0xD6] = 2,
    [0xD8] = 1,
    [0xD9] = 3,
    [0xDD] = 3,
    [0xDE] = 3,

    /* 0xE0 */
    [0xE0] = 2,
    [0xE1] = 2,
    [0xE4] = 2,
    [0xE5] = 2,
    [0xE6] = 2,
    [0xE8] = 1,
    [0xE9] = 2,
    [0xEA] = 1,
    [0xEC] = 3,
    [0xED] = 3,
    [0xEE] = 3,

    /* 0xF0 */
    [0xF0] = 2,
    [0xF1] = 2,
    [0xF5] = 2,
    [0xF6] = 2,
    [0xF8] = 1,
    [0xF9] = 3,
    [0xFD] = 3,
    [0xFE] = 3,
};

addressing_mode_t instruction_addressing_mode[256] = {
    /* 0x00 */
    [0x00] = ADDRESS_IMPLIED,
    [0x01] = ADDRESS_INDEXED_INDIRECT,
    [0x05] = ADDRESS_ZERO_PAGE,
    [0x06] = ADDRESS_ZERO_PAGE,
    [0x08] = ADDRESS_IMPLIED,
    [0x09] = ADDRESS_IMMEDIATE,
    [0x0A] = ADDRESS_ACCUMULATOR,
    [0x0D] = ADDRESS_ABSOLUTE,
    [0x0E] = ADDRESS_ABSOLUTE,

    /* 0x10 */
    [0x10] = ADDRESS_RELATIVE,
    [0x11] = ADDRESS_INDIRECT_INDEXED,
    [0x15] = ADDRESS_ZERO_PAGE_X,
    [0x16] = ADDRESS_ZERO_PAGE_X,
    [0x18] = ADDRESS_IMPLIED,
    [0x19] = ADDRESS_ABSOLUTE_Y,
    [0x1D] = ADDRESS_ABSOLUTE_X,
    [0x1E] = ADDRESS_ABSOLUTE_X,

    /* 0x20 */
    [0x20] = ADDRESS_ABSOLUTE,
    [0x21] = ADDRESS_INDEXED_INDIRECT,
    [0x24] = ADDRESS_ZERO_PAGE,
    [0x25] = ADDRESS_ZERO_PAGE,
    [0x26] = ADDRESS_ZERO_PAGE,
    [0x28] = ADDRESS_IMPLIED,
    [0x29] = ADDRESS_IMMEDIATE,
    [0x2A] = ADDRESS_ACCUMULATOR,
    [0x2C] = ADDRESS_ABSOLUTE,
    [0x2D] = ADDRESS_ABSOLUTE,
    [0x2E] = ADDRESS_ABSOLUTE,

    /* 0x30 */
    [0x30] = ADDRESS_RELATIVE,
    [0x31] = ADDRESS_INDIRECT_INDEXED,
    [0x35] = ADDRESS_ZERO_PAGE_X,
    [0x36] = ADDRESS_ZERO_PAGE_X,
    [0x38] = ADDRESS_IMPLIED,
    [0x39] = ADDRESS_ABSOLUTE_Y,
    [0x3D] = ADDRESS_ABSOLUTE_X,
    [0x3E] = ADDRESS_ABSOLUTE_X,

    /* 0x40 */
    [0x40] = ADDRESS_IMPLIED,
    [0x41] = ADDRESS_INDEXED_INDIRECT,
    [0x45] = ADDRESS_ZERO_PAGE,
    [0x46] = ADDRESS_ZERO_PAGE,
    [0x48] = ADDRESS_IMPLIED,
    [0x49] = ADDRESS_IMMEDIATE,
    [0x4A] = ADDRESS_ACCUMULATOR,
    [0x4C] = ADDRESS_ABSOLUTE,
    [0x4D] = ADDRESS_ABSOLUTE,
    [0x4E] = ADDRESS_ABSOLUTE,

    /* 0x50 */
    [0x50] = ADDRESS_RELATIVE,
    [0x51] = ADDRESS_INDIRECT_INDEXED,
    [0x55] = ADDRESS_ZERO_PAGE_X,
    [0x56] = ADDRESS_ZERO_PAGE_X,
    [0x58] = ADDRESS_IMPLIED,
    [0x59] = ADDRESS_ABSOLUTE_Y,
    [0x5D] = ADDRESS_ABSOLUTE_X,
    [0x5E] = ADDRESS_ABSOLUTE_X,

    /* 0x60 */
    [0x60] = ADDRESS_IMPLIED,
    [0x61] = ADDRESS_INDEXED_INDIRECT,
    [0x65] = ADDRESS_ZERO_PAGE,
    [0x66] = ADDRESS_ZERO_PAGE,
    [0x68] = ADDRESS_IMPLIED,
    [0x69] = ADDRESS_IMMEDIATE,
    [0x6A] = ADDRESS_ACCUMULATOR,
    [0x6C] = ADDRESS_INDIRECT,
    [0x6D] = ADDRESS_ABSOLUTE,
    [0x6E] = ADDRESS_ABSOLUTE,

    /* 0x70 */
    [0x70] = ADDRESS_RELATIVE,
    [0x71] = ADDRESS_INDIRECT_INDEXED,
    [0x75] = ADDRESS_ZERO_PAGE_X,
    [0x76] = ADDRESS_ZERO_PAGE_X,
    [0x78] = ADDRESS_IMPLIED,
    [0x79] = ADDRESS_ABSOLUTE_Y,
    [0x7D] = ADDRESS_ABSOLUTE_X,
    [0x7E] = ADDRESS_ABSOLUTE_X,

    /* 0x80 */
    [0x81] = ADDRESS_INDEXED_INDIRECT,
    [0x84] = ADDRESS_ZERO_PAGE,
    [0x85] = ADDRESS_ZERO_PAGE,
    [0x86] = ADDRESS_ZERO_PAGE,
    [0x88] = ADDRESS_IMPLIED,
    [0x8A] = ADDRESS_IMPLIED,
    [0x8C] = ADDRESS_ABSOLUTE,
    [0x8D] = ADDRESS_ABSOLUTE,
    [0x8E] = ADDRESS_ABSOLUTE,

    /* 0x90 */
    [0x90] = ADDRESS_RELATIVE,
    [0x91] = ADDRESS_INDIRECT_INDEXED,
    [0x94] = ADDRESS_ZERO_PAGE_X,
    [0x95] = ADDRESS_ZERO_PAGE_X,
    [0x96] = ADDRESS_ZERO_PAGE_Y,
    [0x98] = ADDRESS_IMPLIED,
    [0x99] = ADDRESS_ABSOLUTE_Y,
    [0x9A] = ADDRESS_IMPLIED,
    [0x9D] = ADDRESS_ABSOLUTE_X,

    /* 0xA0 */
    [0xA0] = ADDRESS_IMMEDIATE,
    [0xA1] = ADDRESS_INDEXED_INDIRECT,
    [0xA2] = ADDRESS_IMMEDIATE,
    [0xA4] = ADDRESS_ZERO_PAGE,
    [0xA5] = ADDRESS_ZERO_PAGE,
    [0xA6] = ADDRESS_ZERO_PAGE,
    [0xA8] = ADDRESS_IMPLIED,
    [0xA9] = ADDRESS_IMMEDIATE,
    [0xAA] = ADDRESS_IMPLIED,
    [0xAC] = ADDRESS_ABSOLUTE,
    [0xAD] = ADDRESS_ABSOLUTE,
    [0xAE] = ADDRESS_ABSOLUTE,

    /* 0xB0 */
    [0xB0] = ADDRESS_RELATIVE,
    [0xB1] = ADDRESS_INDIRECT_INDEXED,
    [0xB4] = ADDRESS_ZERO_PAGE_X,
    [0xB5] = ADDRESS_ZERO_PAGE_X,
    [0xB6] = ADDRESS_ZERO_PAGE_Y,
    [0xB8] = ADDRESS_IMPLIED,
    [0xB9] = ADDRESS_ABSOLUTE_Y,
    [0xBA] = ADDRESS_IMPLIED,
    [0xBC] = ADDRESS_ABSOLUTE_X,
    [0xBD] = ADDRESS_ABSOLUTE_X,
    [0xBE] = ADDRESS_ABSOLUTE_Y,

    /* 0xC0 */
    [0xC0] = ADDRESS_IMMEDIATE,
    [0xC1] = ADDRESS_INDEXED_INDIRECT,
    [0xC4] = ADDRESS_ZERO_PAGE,
    [0xC5] = ADDRESS_ZERO_PAGE,
    [0xC6] = ADDRESS_ZERO_PAGE,
    [0xC8] = ADDRESS_IMPLIED,
    [0xC9] = ADDRESS_IMMEDIATE,
    [0xCA] = ADDRESS_IMPLIED,
    [0xCC] = ADDRESS_ABSOLUTE,
    [0xCD] = ADDRESS_ABSOLUTE,
    [0xCE] = ADDRESS_ABSOLUTE,

    /* 0xD0 */
    [0xD0] = ADDRESS_RELATIVE,
    [0xD1] = ADDRESS_INDIRECT_INDEXED,
    [0xD5] = ADDRESS_ZERO_PAGE_X,
    [0xD6] = ADDRESS_ZERO_PAGE_X,
    [0xD8] = ADDRESS_IMPLIED,
    [0xD9] = ADDRESS_ABSOLUTE_Y,
    [0xDD] = ADDRESS_ABSOLUTE_X,
    [0xDE] = ADDRESS_ABSOLUTE_X,

    /* 0xE0 */
    [0xE0] = ADDRESS_IMMEDIATE,
    [0xE1] = ADDRESS_INDEXED_INDIRECT,
    [0xE4] = ADDRESS_ZERO_PAGE,
    [0xE5] = ADDRESS_ZERO_PAGE,
    [0xE6] = ADDRESS_ZERO_PAGE,
    [0xE8] = ADDRESS_IMPLIED,
    [0xE9] = ADDRESS_IMMEDIATE,
    [0xEA] = ADDRESS_IMPLIED,
    [0xEC] = ADDRESS_ABSOLUTE,
    [0xED] = ADDRESS_ABSOLUTE,
    [0xEE] = ADDRESS_ABSOLUTE,

    /* 0xF0 */
    [0xF0] = ADDRESS_RELATIVE,
    [0xF1] = ADDRESS_INDIRECT_INDEXED,
    [0xF5] = ADDRESS_ZERO_PAGE_X,
    [0xF6] = ADDRESS_ZERO_PAGE_X,
    [0xF8] = ADDRESS_IMPLIED,
    [0xF9] = ADDRESS_ABSOLUTE_Y,
    [0xFD] = ADDRESS_ABSOLUTE_X,
    [0xFE] = ADDRESS_ABSOLUTE_X,
};


