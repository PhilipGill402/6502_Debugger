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
        default: {
            fprintf(stderr, "Opcode no supported\n");
            return ins;
        }
    }
}
