# RISCAL CPU
RISCAL is a 32-bit custom instruction set architecture virtual machine. It is intended to be used for learning/research purposes. In a nutshell, so far:

* 32-bit, fixed-length instruction set
* 16 General-purpose registers
* FLAGS, stack pointer, base pointer
* 65536 words of program memory (262144 bytes)

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

This will print to stdout all registers for each operation that the VM performs.
