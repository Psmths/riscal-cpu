<p align="center">
  <img class='center' width=200 src='doc/media/rascal.PNG'><br>
  <h2 align="center">RISCAL CPU</h2>
</p>

<p align="center">
  <img src="https://img.shields.io/github/license/Psmths/riscal-cpu.svg">
  <img src="https://img.shields.io/badge/Maintained%3F-yes-green.svg">
  <img src="https://github.com/Psmths/riscal-cpu/workflows/CodeQL/badge.svg">
  <img src="https://github.com/Psmths/riscal-cpu/actions/workflows/c-cpp.yml/badge.svg">
</p>

RISCAL is a 32-bit custom instruction set architecture virtual machine. It is intended to be used for learning/research purposes. In a nutshell, RISCAL provides:

* 32-bit, fixed-length instruction set
* 16 General-purpose registers
* FLAGS, stack pointer, return pointer registers
* 65536 words of program memory, can be extended to 2^32 bytes
* Ability to set up and leverage a return stack to send and retrieve data from RISCAL after exit

.. topic:: Getting Started

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

## Debugging RISCAL

As it stands RISCAL does not have a formal debugger. You can set a debugging flag, however, in the debugger.hpp file:

```
#ifndef DBG_HPP
#define DBG_HPP

#define DEBUG

#endif
```

This will print to stdout all registers for each operation that the VM performs, as well as a stack dump.
