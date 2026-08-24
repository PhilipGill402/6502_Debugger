#ifndef INCLUDE_CLI_H_
#define INCLUDE_CLI_H_

#include <stdint.h>
#include "cpu.h"
#include "instructions/instructions.h"
#include "instructions/tables.h"

#define INPUT_SIZE  1024
#define MAX_ARGS    16

typedef void (*command_fn)(cpu_t* cpu, int8_t argc, char** argv);

typedef struct {
    const char* name;
    command_fn function;
} command_t;

int8_t cli_run(cpu_t* cpu);

#endif
