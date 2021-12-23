# RISCAL CPU



![](https://img.shields.io/github/license/Psmths/riscal-cpu.svg)
![](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![](https://github.com/Psmths/riscal-cpu/workflows/CodeQL/badge.svg)
![](https://github.com/Psmths/riscal-cpu/actions/workflows/c-cpp.yml/badge.svg)

RISCAL is a 32-bit custom instruction set architecture virtual machine. It is intended to be used for learning/research purposes. In a nutshell, RISCAL provides:

* 32-bit, fixed-length instruction set
* 16 General-purpose registers
* FLAGS, stack pointer, return pointer registers
* 65536 words of program memory, can be extended to 2^32 bytes
* Ability to set up and leverage a return stack to send and retrieve data from RISCAL after exit

## Getting Started

This repo comes preloaded with several examples. To build the examples:
```
git clone https://github.com/Psmths/riscal-cpu
cd riscal-cpu
make examples
```

The built examples will be available in the `bin/` directory. 

To leverage RISCAL from a program, use the following methods:
```
unsigned char *run();
void load_rom(unsigned char *rom, int rom_size);
void load_stack(unsigned char *data, int data_size);
```

The easiest way to get starting programming RISCAL is to grab a copy of [customasm](https://github.com/hlorenzi/customasm). This repo contains the custom instruction set definition in the examples directory, in the file riscal.asm to get you started, as well as plenty of supporting examples to use as guides and references.

## Architecture

### Program Memory / Return Stack

RISCAL provides two primary data locations, the PROM and the return stack. When starting RISCAL, you must first load the program memory and the return stack with the corresponding program code and (optionally) the inputs for the program to pull from. RISCAL will execute the PROM and, when execution is stopped by the `HALT` opcode, exit, returning the contents of the return stack. 

### Registers

RISCAL provides 16 general-purpose, 32-bit registers. These registers are addressable by a variety of opcodes. RISCAL provides 'special' registers: The program counter (PC), stack pointer (SP), return pointer (RP) and the FLAGS register (FLAGS). These registers are not addressable by programs, and are only indirectly influenced by certain opcodes. 

### FLAGS Register

The FLAGS register is used to inform branching operations such as JUMP_EQUAL, JUMP_GREATER, etc. It is modified any time an arithmetic operation is performed, such as NOT, ADD, SUBTRACT, XOR, etc.

Bit # | Function | Description
--- | --- | ---
0 | Zero | Enabled if the result of an arithmetic operation is 0
1 | Carry | Enabled if arithmetic operation has performed a carry
2 | Overflow | Enabled if an arithmetic operation has overflowed into a sign bit
3 | Negative | Enabled if the result of an operation is negative (MSB = 1)

### Instruction Set Architecture

RISCAL follows RISC principles with its ISA. Each instruction is fixed-length, meaning that every instruction will consume the same 4 bytes of program memory. This simplifies the control path of the architecture and, accordingly, after each opcode is executed, the program counter will be incremented by 4.

## Debugging RISCAL

As it stands RISCAL does not have a formal debugger. You can set a debugging flag, however, in the debugger.hpp file:

```
#ifndef DBG_HPP
#define DBG_HPP

#define DEBUG

#endif
```

This will print to stdout all registers for each operation that the VM performs, as well as a stack dump.
