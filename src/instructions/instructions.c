#include "instructions/instructions.h"

#include <stdio.h>
#include "instructions/lda.h"

instruction_t instruction_init(uint8_t opcode) {
    instruction_t ins = { 0 }; 

    switch (opcode) {
        case 0xA9: {
            // LDA Immediate 
            ins.opcode = 0xA9;
            ins.bytes = 2;
            ins.cycles = 2;
            ins.execute = lda_immediate;
            return ins;
        }
        case 0xA5: {
            ins.opcode = 0xA5;
            ins.bytes = 2;
            ins.cycles = 3;
            ins.execute = lda_zero_page;
            return ins;
        }
        case 0xB5: {
            ins.opcode = 0xB5;
            ins.bytes = 2;
            ins.cycles = 4;
            ins.execute = lda_zero_page_x;
            return ins;
        }
        case 0xAD: {
            ins.opcode = 0xAD;
            ins.bytes = 3;
            ins.cycles = 4;
            ins.execute = lda_absolute;
            return ins;
        }
        case 0xBD: {
            ins.opcode = 0xBD;
            ins.bytes = 3;
            ins.cycles = 4; // could change to 5
            ins.execute = lda_absolute_x;
            return ins;
        }
        case 0xB9: {
            ins.opcode = 0xB9;
            ins.bytes = 3;
            ins.cycles = 4;
            ins.execute = lda_absolute_y;
            return ins;
        }
        case 0xA1: {
            ins.opcode = 0xA1;
            ins.bytes = 2;
            ins.cycles = 6;
            ins.execute = lda_indirect_x;
            return ins;
        }
        case 0xB1: {
            ins.opcode = 0xB1;
            ins.bytes = 2;
            ins.cycles = 5; // could change to 6
            ins.execute = lda_indirect_y;
            return ins;
        }
        default: {
            fprintf(stderr, "Opcode (%x) not supported\n", opcode);
            return ins;
        }
    }
}
