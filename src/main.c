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
    
    // LDA ($67),Y
    write8(&cpu, 0x0080, 0xB1);
    write8(&cpu, 0x0081, 0x67);
    
    cpu.y = 0x42;
    write8(&cpu, 0x67, 0x69);
    write8(&cpu, 0x69 + 0x42, 0xFF);



    cpu_reset(&cpu);
    
    instruction_t ins = instruction_init(cpu.mem[cpu.pc]);
    ins.execute(&ins, &cpu);

    printf("%x\n", cpu.a);
    print_binary(cpu.status);

    cpu_free(&cpu);
}
