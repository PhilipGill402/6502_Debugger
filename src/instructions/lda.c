#include "instructions/lda.h"

#include <stdio.h>
#include "helpers.h"

static void lda_update_status(cpu_t* cpu) {
    if (cpu->a == 0)
        SET_ZERO(cpu->status);

    if (cpu->a & (1 << 7))
        SET_NEGATIVE(cpu->status);
}


void lda(instruction_t* self, cpu_t* cpu, addressing_mode_t mode) {
    (void)self;
    cpu->pc++;
    
    cpu->a = address(cpu, mode);

    lda_update_status(cpu);
} 

