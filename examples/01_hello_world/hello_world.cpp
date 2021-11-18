/*
    outp | addr | data

     0:0 |    0 |             ; main:
     0:0 |    0 | 10 01 00 1c ; MOVE_LOWER R1, mystring
     4:0 |    4 |             ; loop:
     4:0 |    4 | 0d 00 00 21 ; LOAD_BYTE R2, R1
     8:0 |    8 | 00 a0 00 02 ; PUSH_BYTE R2
     c:0 |    c | 00 50 00 01 ; INCREMENT R1
    10:0 |   10 | 02 00 00 20 ; COMPARE R2, R0
    14:0 |   14 | 70 00 00 04 ; JUMP_NE loop
    18:0 |   18 | 00 10 00 00 ; HALT
    1c:0 |   1c |             ; mystring:
    1c:0 |   1c | 48 65 6c 6c 6f 20 57 6f 72 6c 64 21 ; #d "Hello World!"
    28:0 |   28 | 0a          ; 0x0a
    29:0 |   29 | 00          ; 0x00
*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <cstring>

int main() {
    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    unsigned char rom[] = {
	/* 0x00 */ 0x10, 0x01, 0x00, 0x1c, 0x0d, 0x00, 0x00, 0x21, 0x00, 0xa0, 0x00, 0x02, 0x00, 0x50, 0x00, 0x01,
	/* 0x10 */ 0x02, 0x00, 0x00, 0x20, 0x70, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c,
	/* 0x20 */ 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a, 0x00
    };

    my_cpu->load_rom(rom, sizeof(rom));
    unsigned char* result = my_cpu->run();
    std::cout << result << std::endl;
    return 0;
}
