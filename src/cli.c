#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; --i)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

static void cmd_load(cpu_t* cpu, int8_t argc, char** argv);

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
}

static void cmd_reset(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    cpu_reset(cpu);
}

command_t commands[] = {
    //{ "run",   cmd_run   },
    //{ "step",  cmd_step  },
    { "regs",  cmd_regs  },
    { "mem",   cmd_mem   },
    //{ "write", cmd_write },
    { "reset", cmd_reset },
    { "status", cmd_status },
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
        
        // dispatch command
        if (strcmp(buffer, "exit") == 0)
            break;
        
        for (uint32_t i = 0; i < sizeof(commands) / sizeof(command_t); i++) {
            if (strcmp(buffer, commands[i].name) == 0)
                commands[i].function(cpu, argc, argv);
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

