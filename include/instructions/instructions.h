#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <stdint.h>
#include "instructions/instruction_def.h"

#define REGISTER_INSTRUCTION(ins, op, b, c, fn) \
    do {                                        \
        ins.opcode = (op);                      \
        ins.bytes = (b);                        \
        ins.cycles = (c);                       \
        ins.execute = (fn);                     \
    } while (0)                                 \


instruction_t instruction_init(uint8_t opcode);

#endif
