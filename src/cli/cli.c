#include "cli/cli.h"
#include "cli/breakpoint.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; --i)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

static void cmd_save(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    FILE* save_file = fopen("save.dump", "wb");

    fwrite(cpu->mem, sizeof(uint8_t), MEM_SIZE, save_file);

    fclose(save_file);
}

static void cmd_reload(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    FILE* save_file = fopen("save.dump", "rb");

    fread(cpu->mem, sizeof(uint8_t), MEM_SIZE, save_file);
    cpu_reset(cpu);

    fclose(save_file);
}

static void cmd_next(cpu_t* cpu, int8_t argc, char** argv) {
    uint8_t opcode = read8(cpu, cpu->pc);

    // makes sure current instruction is JSR
    if (opcode == 0x20) { 
        // loops while the current instruction is not RTS
        while (opcode != 0x60) {
            cpu_step(cpu);
            opcode = cpu->pc;
        }
    }
}

static void cmd_write(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "help: %s <address> <value>\n", argv[0]);
        return;
    }

    char* end;
    uint16_t addr = (uint16_t)strtol(argv[1], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address> <value>\n", argv[0]);
        return;
    }

    uint8_t value = (uint8_t)strtol(argv[2], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address> <value>\n", argv[0]);
        return;
    }

    write8(cpu, addr, value);
}

static void cmd_break(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <address>\n", argv[0]);
        return;
    }
    
    char* end;
    uint16_t addr = (uint16_t)strtol(argv[1], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address>\n", argv[0]);
        return;
    }

    add_breakpoint(addr);
}

static void cmd_run(cpu_t* cpu, int8_t argc, char** argv) {
    while (1) {
        if (is_breakpoint(cpu->pc)) {
            printf("Breakpoint reached at %x\n", cpu->pc);
            return;
        }
            
        cpu_step(cpu);
    }
}

static void cmd_load(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <path>\n", argv[0]);
        return;
    }
    
    errno = 0;
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return;
    } 

    uint32_t bytes_read;
    uint16_t addr = read16(cpu, RESET_VECTOR);
    uint8_t buffer[1024];

    do {
        bytes_read = fread(buffer, sizeof(uint8_t), 1024, file);
        memcpy(&cpu->mem[addr], buffer, bytes_read);
        addr += bytes_read;
    } while (bytes_read == 1024);

    fclose(file);
}

static void cmd_regs(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    printf("Register A: %x\n", cpu->a);
    printf("Register X: %x\n", cpu->x);
    printf("Register Y: %x\n", cpu->y);
}

static void cmd_status(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    printf("Status: ");
    print_binary(cpu->status);
}

static void cmd_mem(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <address>\n", argv[0]);
        return;
    }
    
    char* end;
    uint16_t addr = (uint16_t)strtol(argv[1], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address>\n", argv[0]);
        return;
    }

    printf("0x%x\n", cpu->mem[addr]);
}

static void cmd_reset(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    cpu_reset(cpu);
}

static void cmd_step(cpu_t* cpu, int8_t argc, char** argv) {
    uint32_t steps = 1;

    if (argc > 1) {
        char* end; 
        steps = (uint32_t)strtol(argv[1], &end, 0);

        if (*end != '\0') {
            fprintf(stderr, "help: %s [steps]\n", argv[0]);
            return;
        }
    }

    for (uint32_t step = 0; step < steps; ++step)
        cpu_step(cpu); 
}

command_t commands[] = {
    { "run", cmd_run },
    { "step", cmd_step },
    { "regs", cmd_regs },
    { "mem", cmd_mem },
    { "write", cmd_write },
    { "reset", cmd_reset },
    { "status", cmd_status },
    { "load", cmd_load },
    { "break", cmd_break },
    { "next", cmd_next },
    { "save", cmd_save },
    { "reload", cmd_reload },
};

int8_t cli_run(cpu_t* cpu) {
    char buffer[INPUT_SIZE];
    while (1) {
        printf(">> ");
        fflush(stdout);

        errno = 0; 
        void* ret = fgets(buffer, sizeof(buffer), stdin);
        if (!ret) {
            perror("fgets");
            return -1;
        } 
        
        // strip newline
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // get argc and argv
        char* argv[MAX_ARGS] = { 0 };
        
        char* token = strtok(buffer, " ");
        int8_t argc = 0;
        
        while (token) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        
        // dispatch commands
        if (strcmp(buffer, "exit") == 0)
            break;
        
        uint8_t found_function = 0;
        for (uint32_t i = 0; i < sizeof(commands) / sizeof(command_t); i++) {
            if (strcmp(buffer, commands[i].name) == 0) {
                commands[i].function(cpu, argc, argv);
                found_function = 1;
                break;
            }
        }

        if (!found_function)
            printf("Did not recognize command: %s\n", argv[0]);


        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}

