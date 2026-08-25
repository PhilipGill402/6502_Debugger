#include "cpu.h"
#include "instructions/instructions.h"
#include "instructions/tables.h"
#include <stddef.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

cpu_t cpu_init() {
    cpu_t cpu = { 0 };
    
    errno = 0;
    cpu.mem = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (cpu.mem == MAP_FAILED) {
        perror("mmap");
        cpu.mem = NULL;
    }

    return cpu;
}

void cpu_free(cpu_t* cpu) {
    errno = 0;
    if (munmap(cpu->mem, MEM_SIZE) < 0)
        perror("munmap");
}

void cpu_reset(cpu_t* cpu) {
    uint8_t low = cpu->mem[RESET_VECTOR]; 
    uint8_t high = cpu->mem[RESET_VECTOR + 1];

    cpu->pc = (high << 8) | low;

    return;
}

void cpu_step(cpu_t* cpu) {
    instruction_t ins = get_instruction(cpu);
    ins.execute(&ins, cpu, instruction_addressing_mode[ins.opcode]);
}
