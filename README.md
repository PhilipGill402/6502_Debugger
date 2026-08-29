# 6502 Debugger

A command-line NMOS 6502 emulator and debugger written in C.

This project implements the 6502 CPU from the instruction level upward and provides an interactive debugger for loading raw 6502 binaries, stepping through execution, inspecting CPU state, disassembling code, and debugging programs with breakpoints and runtime tools.

> **Status:** Active development.

## Features

### CPU Emulation

- NMOS 6502 CPU model
- 64 KB address space
- Accumulator, X, Y, stack pointer, program counter, and processor status registers
- 6502 stack at `$0100-$01FF`
- Reset-vector handling
- Official documented addressing modes
- Opcode dispatch tables
- Raw binary loading
- Instruction-level tests

### Debugger

- Interactive command-line interface
- Single-step and multi-step execution
- Register inspection
- Processor-status inspection
- Memory inspection
- Breakpoints
- 6502 disassembly
- Debugger script execution
- Watchpoint support under development

## Project Structure

```text
6502_Debugger/
├── include/
│   ├── instructions/
│   ├── cli.h
│   ├── cpu.h
│   └── helpers.h
├── src/
│   ├── instructions/
│   ├── cli.c
│   ├── cpu.c
│   └── main.c
├── test/
├── Makefile
└── README.md
```

## Building

### Requirements

- `clang`
- `make`
- C11-compatible development environment
- POSIX-compatible system

Clone:

```bash
git clone https://github.com/PhilipGill402/6502_Debugger.git
cd 6502_Debugger
```

Build:

```bash
make
```

Run:

```bash
./emu
```

or:

```bash
make run
```

Clean:

```bash
make clean
```

## Loading 6502 Programs

The debugger loads raw 6502 machine-code binaries directly into emulated memory.

Example source:

```asm
        org $8000

        lda #$42
        tax
        inx
        brk
```

Assemble with vasm:

```bash
vasm6502_oldstyle -Fbin program.s -o program.bin
```

Inspect the bytes:

```bash
hexdump -C program.bin
```

Example output:

```text
00000000  a9 42 aa e8 00
```

Then load it in the debugger:

```text
>> load program.bin
```

## Debugger Commands

### `load <path>`

Load a raw 6502 binary.

```text
>> load program.bin
```

### `step [count]`

Execute one instruction, or an optional number of instructions.

```text
>> step
>> step 10
```

### `regs`

Display CPU registers.

```text
>> regs
```

### `status`

Display the processor status register.

```text
>> status
```

### `mem <address>`

Inspect memory.

```text
>> mem 0x8000
```

### `reset`

Reload the program counter from the reset vector.

```text
>> reset
```

### Breakpoints

Breakpoints stop execution when the program counter exactly reaches a selected instruction address, before that instruction executes.

```text
>> break 0x8010
>> run
Breakpoint hit at $8010
```

### Disassembly

The debugger includes a 6502 disassembler for converting machine code back into readable assembly.

```text
$8000: A9 42       LDA #$42
$8002: AA          TAX
$8003: E8          INX
$8004: D0 FC       BNE $8002
```

Disassembly is useful while stepping, on breakpoint hits, and when identifying the instruction responsible for a watched memory access.

### Debugger Scripts

Debugger commands can be read from script files so common debugging sessions can be repeated automatically.

Example:

```text
load program.bin
break 0x8010
run
regs
```

### Watchpoints

Watchpoint support is being developed to stop execution when selected memory addresses are read from or written to.

The debugger tracks the address of the currently executing instruction separately from the live program counter, allowing a watchpoint to identify and disassemble the instruction that caused the access even after `PC` has advanced.

## 6502 Memory Layout

```text
$0000 -----------------
       Zero Page
$00FF -----------------

$0100 -----------------
       Hardware Stack
$01FF -----------------

       General Memory

$8000 -----------------
       Typical Program
       Load Address

$FFFC -----------------
       Reset Vector
$FFFD -----------------

$FFFE -----------------
       IRQ / BRK Vector
$FFFF -----------------
```

Raw binaries do not contain load-address metadata. The debugger decides where the first byte is placed in emulated memory.

## Addressing Modes

The emulator supports the documented NMOS 6502 addressing modes:

- Implied
- Accumulator
- Immediate
- Zero Page
- Zero Page,X
- Zero Page,Y
- Relative
- Absolute
- Absolute,X
- Absolute,Y
- Indirect
- Indexed Indirect `($nn,X)`
- Indirect Indexed `($nn),Y`

The implementation also handles 6502-specific behavior such as zero-page wrapping and the NMOS indirect `JMP` page-boundary behavior.

## Stack Behavior

The stack occupies `$0100-$01FF`, with the 8-bit stack pointer acting as an offset into that page.

A push:

1. Writes to `$0100 + SP`
2. Decrements `SP`

A pull:

1. Increments `SP`
2. Reads from `$0100 + SP`

This is used by instructions including `PHA`, `PHP`, `PLA`, `PLP`, `JSR`, `RTS`, `BRK`, and `RTI`.

## Tests

Tests live under:

```text
test/
```

They are used to validate:

- Instruction behavior
- Addressing modes
- Status flags
- Stack operations
- Register transfers
- Branching
- Arithmetic and comparisons
- Memory reads and writes
- Zero-page wrapping
- Indirect addressing

## Current Development Priorities

- Complete watchpoint behavior
- Continuous execution / `run`
- Breakpoint management
- Step-over / `next` for `JSR`
- Instruction tracing
- Execution history
- Stack inspection
- Improved memory dumps
- Cycle accounting
- Better processor-state display
- Symbol support
- Conditional breakpoints
- Additional emulator validation

## Goals

The project is intended both as a usable debugger and as a low-level exploration of CPU architecture, including:

- Instruction decoding
- Machine-code execution
- Addressing modes
- Registers and flags
- Stack behavior
- Subroutine calls and returns
- Interrupt behavior
- Memory access
- Binary loading
- Disassembly
- Breakpoints
- Watchpoints
- Debugger architecture

The emulator and debugger are implemented directly in C rather than relying on an existing 6502 emulation library.

## License

No license has currently been specified.

## Author

Philip Gill
