#include <stdio.h>
#include "helpers.h"
#include "cpu.h"
#include "instructions/instructions.h"
#include "cli.h"

int main() {
    cpu_t cpu = cpu_init();
    if (cpu.mem == NULL)
        return -1;
    
    // hard coding reset vectors
    write16(&cpu, RESET_VECTOR, 0x8000);

    cpu_reset(&cpu);
    
    int8_t ret = cli_run(&cpu); 

    cpu_free(&cpu);
    
    return ret;
}
