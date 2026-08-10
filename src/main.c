#include <stdio.h>
#include "cpu.h"
#include "instructions/instructions.h"

static void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; --i)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

int main() {
    cpu_t cpu = cpu_init();
    if (cpu.mem == NULL)
        return -1;
    
    // hard coding reset vectors
    cpu.mem[0xFFFC] = 0x80;
    cpu.mem[0xFFFD] = 0x00;

    // LDA #67
    cpu.mem[0x0080] = 0xA9;
    cpu.mem[0x0081] = 0xFF;

    cpu_reset(&cpu);

    instruction_t ins = instruction_init(cpu.mem[cpu.pc]);
    ins.execute(&cpu);

    printf("%x\n", cpu.a);
    print_binary(cpu.status);

    cpu_free(&cpu);
}
