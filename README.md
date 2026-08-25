# 6502 Debugger

A command-line debugger and emulator for the NMOS 6502 microprocessor, written in C.

This project implements the core behavior of the 6502 CPU and provides an interactive CLI for loading raw 6502 binaries, stepping through instructions, and inspecting processor state and memory.

## Features

- NMOS 6502 CPU emulation
- 64 KB address space
- 6502 addressing modes
- Instruction dispatch through opcode and addressing-mode tables
- Stack behavior using the 6502 stack page at `$0100-$01FF`
- Reset-vector startup
- Raw binary loading
- Single-step and multi-step execution
- Register inspection
- Processor-status inspection
- Memory inspection
- Unit tests for CPU instructions and addressing behavior
- Interactive command-line interface

## Building

### Requirements

- C11-compatible compiler
- `clang`
- `make`
- POSIX-compatible environment

Clone the repository:

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
./6502_debug
```

or:

```bash
make run
```

Clean:

```bash
make clean
```

## Using the Debugger

Starting the program opens an interactive prompt:

```text
>>
```

The CPU currently uses `$8000` as the reset address.

### Commands

#### `load <path>`

Loads a raw binary file into emulated memory beginning at the current reset-vector address.

```text
>> load programs/test.bin
```

#### `break <address>

Suspends execution of the program at a given address.

```text
>> break 0x8000
```

#### `run`

Executes instructions either indefinitely or until a breakpoint is reached.

```text
>> run
```

#### `step [count]`

Executes one instruction by default, or multiple instructions if a count is provided.

```text
>> step
>> step 10
```

#### `regs`

Displays the CPU registers.

```text
>> regs
```

#### `status`

Displays the processor status register.

```text
>> status
```

#### `mem <address>`

Displays memory at the supplied address.

```text
>> mem 0x8000
```

#### `reset`

Reloads the program counter from the 6502 reset vector at `$FFFC-$FFFD`.

```text
>> reset
```

#### `exit`

Exits the debugger.

```text
>> exit
```

## Loading 6502 Programs

The debugger expects a raw binary containing 6502 machine code.

For example:

```asm
        org $8000

        lda #$42
        tax
        inx
        brk
```

Assemble it was any assembler, I use vasm here:

```bash
vasm6502_oldstyle -Fbin program.s -o program.bin
```

Then load it:

```text
>> load program.bin
```

## Example Session

```text
>> load program.bin
>> step
>> regs
Register A: 42
Register X: 0
Register Y: 0

>> step
>> regs
Register A: 42
Register X: 42
Register Y: 0

>> step
>> regs
Register A: 42
Register X: 43
Register Y: 0
```

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
       Current Program
       Load Address

$FFFC -----------------
       Reset Vector
$FFFD -----------------

$FFFE -----------------
       IRQ / BRK Vector
$FFFF -----------------
```

## CPU State

The emulator tracks:

```text
A   Accumulator
X   X index register
Y   Y index register
SP  Stack pointer
PC  Program counter
P   Processor status
```

## Tests

Tests are located under:

```text
test/
```

They verify behavior such as:

- Instruction execution
- Addressing modes
- Status flags
- Stack push/pull behavior
- Branch behavior
- Register transfers
- Memory reads and writes

## Current Status

The project is under active development.

Planned debugger features include:

- Memory write command
- Improved register display
- Disassembly
- Cycle tracking

## Goals

The goal of this project is to build a usable 6502 debugging environment while learning the low-level behavior of a CPU, including:

- instruction decoding
- addressing modes
- registers
- status flags
- stack behavior
- interrupts
- memory
- binary program execution

