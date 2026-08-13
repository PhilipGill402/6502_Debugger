#ifndef INCLUDE_CPU_H_
#define INCLUDE_CPU_H_

#include <stdint.h>

#define MEM_SIZE 65536

#define SET_CARRY(status) status = status | 1
#define CLEAR_CARRY(status) status = status & ~(1)

#define SET_ZERO(status) status = status | 1 << 1
#define CLEAR_ZERO(status) status = status & ~(1 << 1)

#define SET_INTERRUPT_DISABLE(status) status = status | 1 << 2
#define CLEAR_INTERRUPT_DISABLE(status) status = status & ~(1 << 2)

#define SET_DECIMAL(status) status = status | 1 << 3
#define CLEAR_DECIMAL(status) status = status & ~(1 << 3)

#define SET_BREAK(status) status = status | 1 << 4
#define CLEAR_BREAK(status) status = status & ~(1 << 4)

#define SET_OVERFLOW(status) status = status | 1 << 5
#define CLEAR_OVERFLOW(status) status = status & ~(1 << 5)

#define SET_NEGATIVE(status) status = status | 1 << 6
#define CLEAR_NEGATIVE(status) status = status & ~(1 << 6)

#define CARRY       1 << 1
#define ZERO        1 << 2
#define INTERRUPT   1 << 3
#define DECIMAL     1 << 4
#define BREAK       1 << 5
#define NEGATIVE    1 << 6

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
} cpu_t;

cpu_t cpu_init();
void cpu_free(cpu_t* cpu);
void cpu_reset(cpu_t* cpu);

#endif
