#include "instructions/lda.h"

void lda_immediate(cpu_t* cpu) {
    uint8_t opcode = cpu->mem[cpu->pc++]; // opcode
    uint8_t value = cpu->mem[cpu->pc++]; // value to be loaded in
    
    cpu->a = value;

    if (cpu->a == 0)
        SET_ZERO(cpu->status);

    if (cpu->a & (1 << 7))
        SET_NEGATIVE(cpu->status);
}
