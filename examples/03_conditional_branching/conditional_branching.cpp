/*
    conditional_branching.cpp - Example demonstrating register comparison and
    subsequent conditional branching operations.

    outp | addr | data

      0:0 |    0 |             ; main:
      0:0 |    0 | 00 00 00 10 ; CLEAR R0
      4:0 |    4 | 00 00 00 11 ; CLEAR R1
      8:0 |    8 | 00 11 00 03 ; MOVE_LOWER R1, 3
      c:0 |    c | 00 12 00 10 ; MOVE_LOWER R2, loop
     10:0 |   10 |             ; loop:
     10:0 |   10 | 00 00 00 20 ; INCREMENT R0
     14:0 |   14 | 00 00 01 01 ; COMPARE R0, R1
     18:0 |   18 | 00 00 00 92 ; JUMP_NE R2
     1c:0 |   1c | 00 00 00 01 ; HALT
*/

#include "../../include/cpu.hpp"

int main() {
    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    cpu_word rom[8] = { 0x00000010,
                        0x00000011,
                        0x00110003,
                        0x00120010,
                        0x00000020,
                        0x00000101,
                        0x00000092,
                        0x00000001};

    my_cpu->load_rom(rom, sizeof(rom));
    char* result = my_cpu->run();

    return 0;
}
