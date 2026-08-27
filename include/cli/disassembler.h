#ifndef INCLUDE_CLI_DISASSEMBLER_H_
#define INCLUDE_CLI_DISASSEMBLER_H_

#include <stdint.h>
#include "cpu.h"

#define BUFFER_SIZE 256

char* disassemble_line(cpu_t* cpu, uint16_t* addr);

#endif
