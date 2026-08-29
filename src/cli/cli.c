#include "cli/cli.h"
#include "cli/breakpoint.h"
#include "cli/disassembler.h"
#include "cli/watchlist.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void cmd_run(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_step(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_regs(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_mem(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_write(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_reset(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_status(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_load(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_break(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_next(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_save(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_reload(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_disassemble(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_script(cpu_t* cpu, int8_t argc, char** argv);
static void cmd_watch(cpu_t* cpu, int8_t argc, char** argv);

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
    { "disassemble", cmd_disassemble },
    { "script", cmd_script },
    { "watch", cmd_watch },
};

static void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; --i)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

static uint8_t dispatch_command(cpu_t* cpu, char* buffer) {
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
            return 0;
        
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

        return 1;
}

static void cmd_watch(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <address>\n", argv[0]);
        return;
    }

    char* end;
    uint16_t addr = (uint16_t)strtol(argv[1], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address> [lines]\n", argv[0]);
        return;
    }

    watch_point_add(addr);
}

static void cmd_script(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <path>\n", argv[0]);
        return;
    }
    
    errno = 0;
    FILE* script = fopen(argv[1], "r");
    if (!script) {
        perror("fopen");
        return;
    }
    
    char buffer[256];
    uint64_t i = 0;
    while (fgets(buffer, 256, script)) {
        size_t len = strlen(buffer);
        buffer[len - 1] = '\0';
        printf("[%llu] %s\n", i++, buffer);
        
        dispatch_command(cpu, buffer);
    }

    fclose(script);
}

static void cmd_disassemble(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <address> [lines]\n", argv[0]);
        return;
    }
    
    char* end;
    uint16_t addr = (uint16_t)strtol(argv[1], &end, 0);

    if (*end != '\0') {
        fprintf(stderr, "help: %s <address> [lines]\n", argv[0]);
        return;
    }

    uint16_t lines = 1;
    if (argc >= 3) {
        char* end;
        lines = (uint16_t)strtol(argv[2], &end, 0);

        if (*end != '\0') {
            fprintf(stderr, "help: %s <address> [lines]\n", argv[0]);
            return;
        }
    }

    for (uint16_t i = 0; i < lines; ++i) {
        char* line = disassemble_line(cpu, &addr);
        printf("%s\n", line); 
        free(line);
    }
    
    
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
    (void)argc;
    (void)argv;

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
            printf("Breakpoint reached\n");
            uint16_t addr = cpu->pc;
            char* line = disassemble_line(cpu, &addr);
            printf("%s\n", line);
            free(line);
            return;
        } 

        int32_t addr = watch_point_is_active();
        if (addr != -1) {
            printf("Watch Point activated\n");
            watch_point_reset(addr);
            uint16_t pc = cpu->previous_instruction;
            char* line = disassemble_line(cpu, &pc);
            printf("%s\n", line);
            free(line);

            return;
        }
            
        cpu_step(cpu);
    }
}

static void cmd_load(cpu_t* cpu, int8_t argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "help: %s <path> [address]\n", argv[0]);
        return;
    }
    
    uint16_t addr = read16(cpu, RESET_VECTOR);
    if (argc >= 3) {
        char* end;
        addr = (uint16_t)strtol(argv[2], &end, 0);

        if (*end != '\0') {
            fprintf(stderr, "help: %s <path> [address]\n", argv[0]);
            return;
        }

        cpu->pc = addr;
    } 
    
    
    errno = 0;
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return;
    } 

    uint32_t bytes_read;
    uint8_t buffer[1024];
    uint16_t start_addr = addr;
    
    do {
        bytes_read = fread(buffer, sizeof(uint8_t), 1024, file);
        memcpy(&cpu->mem[addr], buffer, bytes_read);
        addr += bytes_read;
    } while (bytes_read == 1024);

    fclose(file);

    printf("Loaded %s at 0x%04x\n", argv[1], start_addr);
}

static void cmd_regs(cpu_t* cpu, int8_t argc, char** argv) {
    (void)argc;
    (void)argv;

    printf("Register A: %d\n", cpu->a);
    printf("Register X: %d\n", cpu->x);
    printf("Register Y: %d\n", cpu->y);
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

    for (uint32_t step = 0; step < steps; ++step) {
        uint16_t addr = cpu->pc;
        char* line = disassemble_line(cpu, &addr);
        printf("%s\n", line);
        free(line);
        cpu_step(cpu);
    }
         
}

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
        if (!dispatch_command(cpu, buffer))
            break;
        
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}

