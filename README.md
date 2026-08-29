# 6502 Debugger

A command-line NMOS 6502 emulator and debugger written in C.

This project implements the 6502 CPU from the instruction level upward and provides an interactive debugger for loading raw 6502 binaries, stepping through execution, inspecting CPU state, disassembling code, and debugging programs with breakpoints, watchpoints, scripts, and runtime tools.

## Features

### CPU Emulation

* NMOS 6502 CPU model
* 64 KB address space
* Accumulator, X, Y, stack pointer, program counter, and processor status registers
* 6502 stack at `$0100-$01FF`
* Reset-vector handling
* Official documented addressing modes
* Opcode dispatch tables
* Raw binary loading
* Instruction-level tests

### Debugger

* Interactive command-line interface
* Single-step and multi-step execution
* Continuous execution
* CPU state inspection
* Memory inspection and modification
* Breakpoints
* Watchpoints
* 6502 disassembly
* Step-over support for subroutines
* Stack inspection
* Debugger script execution
* Memory save/reload support

## Building

### Requirements

* `clang`
* `make`
* C11-compatible development environment
* POSIX-compatible system

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

Assemble:

```bash
vasm6502_oldstyle -Fbin program.s -o program.bin
```

Then load it in the debugger:

```text
>> load program.bin
```

A custom load address can also be provided:

```text
>> load program.bin 0x9000
```

## Debugger Commands

### `run`

Continuously execute instructions until execution is stopped by a breakpoint or watchpoint.

```text
>> run
```

When a breakpoint is reached, the debugger prints the instruction at the breakpoint address.

```text
Breakpoint reached
0x8010: LDA #$42
```

When a watchpoint is triggered, the debugger displays the instruction that caused the watched memory access.

---

### `step [steps]`

Execute one instruction by default.

```text
>> step
```

An optional number of instructions can be provided:

```text
>> step 10
```

Each instruction is disassembled before it executes.

---

### `next`

Step over a subroutine call.

When the current instruction is a `JSR`, `next` executes the subroutine rather than stopping on each instruction inside it.

```text
>> next
```

This is intended to allow debugging code such as:

```asm
JSR subroutine
LDA #$42
```

without manually stepping through the entire subroutine.

---

### `state`

Display the current CPU state.

```text
>> state
```

The command displays:

* Program counter
* Stack pointer
* Accumulator
* X register
* Y register
* Processor status flags
* The instruction currently pointed to by `PC`

Example:

```text
PC: 0x8000    SP: 0xfd
A:  0x0042    X: 0x0000    Y: 0x0000
Status: -NVBDIZC
        00000000

0x8000: LDA #$42
```

---

### `mem <address>`

Inspect one byte of memory.

```text
>> mem 0x8000
```

Numeric arguments may be provided using normal C-style notation, including hexadecimal values such as `0x8000`.

---

### `write <address> <value>`

Write one byte to emulated memory.

```text
>> write 0x8000 0xea
```

This can be useful for modifying code or data while debugging.

---

### `reset`

Reset the CPU.

```text
>> reset
```

The program counter is reloaded using the configured 6502 reset behavior.

---

### `load <path> [address]`

Load a raw binary into emulated memory.

```text
>> load program.bin
```

By default, the program is loaded at the address stored in the reset vector.

An optional address can override the load location:

```text
>> load program.bin 0x9000
```

When a custom address is provided, the program counter is also set to that address.

Example output:

```text
Loaded program.bin at 0x9000
```

---

### `break <address>`

Add a breakpoint at an instruction address.

```text
>> break 0x8010
```

Breakpoints are checked against the program counter during `run`.

When execution reaches the exact breakpoint address, execution stops before that instruction executes.

```text
>> run
Breakpoint reached
0x8010: LDA #$42
```

---

### `watch <address>`

Add a watchpoint for a memory address.

```text
>> watch 0x0200
```

A watchpoint is used to detect accesses to the watched location while the CPU executes.

When a watchpoint becomes active, `run` stops and disassembles the instruction that caused the memory access.

Example:

```text
Watch Point activated
0x8014: STA $0200
```

---

### `disassemble <address> [lines]`

Disassemble machine code beginning at an address.

```text
>> disassemble 0x8000
```

By default, one instruction is displayed.

An optional number of instructions can be provided:

```text
>> disassemble 0x8000 5
```

Example:

```text
0x8000: LDA #$42
0x8002: TAX
0x8003: INX
0x8004: JSR $9000
0x8007: STA $0200
```

The disassembler uses the opcode and addressing mode to determine how many bytes belong to each instruction.

---

### `stack [num values]`

Inspect values around the current stack pointer.

```text
>> stack
```

By default, five stack values are displayed.

You can optionally specify how many values to print:

```text
>> stack 10
```

Example:

```text
SP: 0xfd
0x01fd: 0x34
0x01fe: 0x12
0x01ff: 0x80
```

The 6502 stack occupies `$0100-$01FF`.

---

### `script <path>`

Execute debugger commands from a script file.

```text
>> script debug.txt
```

Example script:

```text
load program.bin
break 0x8010
run
state
stack
```

Commands are executed in order and echoed as the script runs.

Example:

```text
[0] load program.bin
[1] break 0x8010
[2] run
[3] state
```

This makes it possible to repeat common debugging workflows automatically.

---

### `save`

Save the entire 64 KB emulated memory image to:

```text
save.dump
```

Usage:

```text
>> save
```

This writes the current contents of CPU memory to disk.

---

### `reload`

Reload memory from:

```text
save.dump
```

Usage:

```text
>> reload
```

After restoring memory, the CPU is reset.

This can be useful for returning to a previously saved emulator state without reloading the original program manually.

---

### `exit`

Exit the debugger.

```text
>> exit
```

## Example Debugging Session

```text
>> load program.bin
Loaded program.bin at 0x8000

>> disassemble 0x8000 4
0x8000: LDA #$42
0x8002: TAX
0x8003: INX
0x8004: STA $0200

>> break 0x8004

>> run
Breakpoint reached
0x8004: STA $0200

>> state
PC: 0x8004    SP: 0xfd
A:  0x0042    X: 0x0043    Y: 0x0000
Status: -NVBDIZC
        00000000

0x8004: STA $0200

>> watch 0x0200

>> run
Watch Point activated
0x8004: STA $0200

>> mem 0x0200
0x42
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

* Implied
* Accumulator
* Immediate
* Zero Page
* Zero Page,X
* Zero Page,Y
* Relative
* Absolute
* Absolute,X
* Absolute,Y
* Indirect
* Indexed Indirect `($nn,X)`
* Indirect Indexed `($nn),Y`

The implementation also handles 6502-specific behavior such as zero-page wrapping and the NMOS indirect `JMP` page-boundary behavior.

## Stack Behavior

The stack occupies `$0100-$01FF`, with the 8-bit stack pointer acting as an offset into that page.

A push:

1. Writes to `$0100 + SP`
2. Decrements `SP`

A pull:

1. Increments `SP`
2. Reads from `$0100 + SP`

This is used by instructions including:

* `PHA`
* `PHP`
* `PLA`
* `PLP`
* `JSR`
* `RTS`
* `BRK`
* `RTI`

## Tests

Tests live under:

```text
test/
```

They are used to validate:

* Instruction behavior
* Addressing modes
* Status flags
* Stack operations
* Register transfers
* Branching
* Arithmetic and comparisons
* Memory reads and writes
* Zero-page wrapping
* Indirect addressing

## Goals

The project is intended both as a usable debugger and as a low-level exploration of CPU architecture, including:

* Instruction decoding
* Machine-code execution
* Addressing modes
* Registers and flags
* Stack behavior
* Subroutine calls and returns
* Interrupt behavior
* Memory access
* Binary loading
* Disassembly
* Breakpoints
* Watchpoints
* Scriptable debugging
* Debugger architecture

The emulator and debugger are implemented directly in C rather than relying on an existing 6502 emulation library.

## Author

Philip Gill

