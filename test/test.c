#include "test.h"
#include "../include/instructions/addressing_modes.h"
#include "../include/instructions/instruction_def.h"
#include "../include/instructions/instructions.h"
#include "../include/cpu.h"
#include "../include/helpers.h"
#include <assert.h>
#include <stdio.h>

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

static void test_lda(cpu_t* cpu) {
    test_instruction(cpu, 0xA9, 0x99, -1);
    assert(cpu->a == 0x99);
    
    write8(cpu, 0x99, 0x67);
    test_instruction(cpu, 0xA5, 0x99, -1);
    assert(cpu->a == 0x67);
}

void test() {
    cpu_t cpu = cpu_init();
    if (cpu.mem == NULL)
        return;
    
    // hard coding reset vectors
    write8(&cpu, 0xFFFC, 0x80);
    write8(&cpu, 0xFFFD, 0x00);

    cpu_reset(&cpu);

    test_lda(&cpu);    

    cpu_free(&cpu);
    return;
}
