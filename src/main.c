#include <stdio.h>
#include "cpu.h"

int main() {
    cpu_t cpu = cpu_init();
    if (cpu.mem == NULL)
        return -1;
    
    // hard coding reset vectors
    cpu.mem[0xFFFC] = 0x80;
    cpu.mem[0xFFFD] = 0xFF;
    cpu_reset(&cpu);

    printf("%x\n", cpu.pc);

    cpu_free(&cpu);
}
