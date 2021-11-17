/*
    ascii_lowercase.cpp - Example demonstrating logical lowercase operation on
    ASCII characters.

    outp | addr | data
     0:0 |    0 |             ; test:
     0:0 |    0 | 00 12 00 1c ; MOVE_LOWER R2, myword
     4:0 |    4 | 00 13 00 20 ; MOVE_LOWER R3, invert
     8:0 |    8 | 00 00 0a 02 ; LOAD_WORD R0, R2
     c:0 |    c | 00 00 0a 13 ; LOAD_WORD R1, R3
    10:0 |   10 | 00 00 06 01 ; XOR R0, R1
    14:0 |   14 | 00 00 00 50 ; PUSH_WORD R0
    18:0 |   18 | 00 00 00 01 ; HALT
    1c:0 |   1c |             ; myword:
    1c:0 |   1c | 41 41 41 41 ; #d32 0x41414141
    20:0 |   20 |             ; invert:
    20:0 |   20 | 20 20 20 20 ; #d32 0x20202020
*/

#include "../../src/cpu.cpp"

int main() {
    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    cpu_word rom[9] = {0x0012001c,
                        0x00130020,
                        0x00000a02,
                        0x00000a13,
                        0x00000601,
                        0x00000050,
                        0x00000001,
                        0x41414141,
                        0x20202020};

    my_cpu->load_rom(rom, sizeof(rom));
    char* result = my_cpu->run();

    std::cout << "Return value: " << result << std::endl;

    return 0;
}
