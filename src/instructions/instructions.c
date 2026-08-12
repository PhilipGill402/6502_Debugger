#include "instructions/instructions.h"

#include <stdio.h>
#include "instructions/lda.h"
#include "instructions/ldx.h"

instruction_t instruction_init(uint8_t opcode) {
    instruction_t ins = { 0 }; 

    switch (opcode) {
        case 0xA9: {
            REGISTER_INSTRUCTION(ins, 0xA9, 2, 2, lda_immediate);
            return ins;
        }
        case 0xA5: {
            REGISTER_INSTRUCTION(ins, 0xA5, 2, 3, lda_zero_page); 
            return ins;
        }
        case 0xB5: {
            REGISTER_INSTRUCTION(ins, 0xB5, 2, 4, lda_zero_page_x);
            return ins;
        }
        case 0xAD: {
            REGISTER_INSTRUCTION(ins, 0xAD, 3, 4, lda_absolute);
            return ins;
        }
        case 0xBD: {
            // cycles could change to 5 
            REGISTER_INSTRUCTION(ins, 0xBD, 3, 4, lda_absolute_x);
            return ins;
        }
        case 0xB9: {
            // cycles could change to 5
            REGISTER_INSTRUCTION(ins, 0xB9, 3, 4, lda_absolute_y);
            return ins;
        }
        case 0xA1: {
            REGISTER_INSTRUCTION(ins, 0xA1, 2, 6, lda_indirect_x); 
            return ins;
        }
        case 0xB1: {
            // cycles could change to 6
            REGISTER_INSTRUCTION(ins, 0xB1, 2, 5, lda_indirect_y);
            return ins;
        }
        case 0xA2: {
            REGISTER_INSTRUCTION(ins, 0xA2, 2, 3, ldx_immediate);
            return ins;
        }
        case 0xA6: {
            REGISTER_INSTRUCTION(ins, 0xA6, 2, 3, ldx_zero_page); 
            return ins;
        }
        case 0xB6: {
            REGISTER_INSTRUCTION(ins, 0xB6, 2, 4, ldx_zero_page_y);
            return ins;
        }
        case 0xAE: {
            REGISTER_INSTRUCTION(ins, 0xAE, 3, 4, ldx_absolute);
            return ins;
        }
        case 0xBE: {
            // cycles could change to 5
            REGISTER_INSTRUCTION(ins, 0xBE, 3, 4, ldx_absolute_y);
        }
        default: {
            fprintf(stderr, "Opcode (%x) not supported\n", opcode);
            return ins;
        }
    }
}
