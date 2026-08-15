#include <stdio.h>
#include "helpers.h"
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
    write8(&cpu, 0xFFFC, 0x80);
    write8(&cpu, 0xFFFD, 0x00);
    
    write8(&cpu, 0x0080, 0x29);
    write8(&cpu, 0x0081, 0xab);
    cpu.a = 0x01;
    
    write8(&cpu, 0x0067, 0x69);
    
    cpu_reset(&cpu);
    
    instruction_t ins = instruction_init(cpu.mem[cpu.pc]);
    ins.execute(&ins, &cpu, ins.mode);
    
    print_binary(cpu.a);
    printf("%x\n", cpu.a);
    print_binary(cpu.status);

    cpu_free(&cpu);
}
