# RISCAL CPU

![](https://img.shields.io/github/license/Psmths/riscal-cpu.svg)
![](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![](https://github.com/Psmths/riscal-cpu/workflows/CodeQL/badge.svg)

RISCAL is a 32-bit custom instruction set architecture virtual machine. It is intended to be used for learning/research purposes. In a nutshell, so far:

* 32-bit, fixed-length instruction set
* 16 General-purpose registers
* FLAGS, stack pointer, return pointer registers
* 65536 words of program memory, can be extended to 2^16 bytes
* Ability to set up and leverage a return stack to send and retrieve data from RISCAL after exit

## Getting Started
This repo comes preloaded with several examples. To build the examples:
```
git clone https://github.com/Psmths/riscal-cpu
cd riscal-cpu
make examples
cd bin
```

To leverage RISCAL from a program, use the following methods:
```
unsigned char *run();
void load_rom(unsigned char *rom, int rom_size);
void load_stack(unsigned char *data, int data_size);
```

## Assembling for RISCAL
The easiest way to get starting programming RISCAL is to grab a copy of [customasm](https://github.com/hlorenzi/customasm). This repo contains the custom instruction set definition in the examples directory, in the file riscal.asm to get you started, as well as a small loop test program.

## Debugging RISCAL
As it stands RISCAL does not have a formal debugger. You can set a debugging flag, however, in the debugger.hpp file:

```
#ifndef DBG_HPP
#define DBG_HPP

#define DEBUG

#endif
```

This will print to stdout all registers for each operation that the VM performs, as well as a stack dump.
