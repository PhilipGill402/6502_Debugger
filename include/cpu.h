#ifndef INCLUDE_CPU_H_
#define INCLUDE_CPU_H_

#include <stdint.h>

#define MEM_SIZE            65536
#define STACK_START         0x0100
#define INTERRUPT_VECTOR    0xFFFE
#define RESET_VECTOR        0xFFFC

#define CARRY       1 << 1
#define ZERO        1 << 2
#define INTERRUPT   1 << 3
#define DECIMAL     1 << 4
#define BREAK       1 << 5
#define OVERFLOW    1 << 6
#define NEGATIVE    1 << 7

typedef struct {
    // registers
    uint16_t pc;
    uint8_t sp;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t status;
    
    // memory
    uint8_t* mem;

    // debug info
    uint16_t previous_instruction;
} cpu_t;

static inline void set_flag(cpu_t* cpu, uint8_t flag, uint8_t value) {
    if (value)
        cpu->status |= flag;
    else
        cpu->status &= ~flag;
}

static inline uint8_t test_flag(cpu_t* cpu, uint8_t flag) {
    return cpu->status & flag;
}

cpu_t cpu_init();
void cpu_free(cpu_t* cpu);
void cpu_reset(cpu_t* cpu);
void cpu_step(cpu_t* cpu);

#endif
