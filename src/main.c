#include <stdio.h>
#include "helpers.h"
#include "cpu.h"
#include "instructions/instructions.h"

#include "test.h"

static void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; --i)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

int main() {
    test(); 
}
