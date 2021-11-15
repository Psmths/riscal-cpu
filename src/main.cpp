#include "../include/cpu.hpp"
#include "cpu.cpp"
#include <iostream>
#include <stdint.h>

int main() {
    /* currently very rudimetary unit test */
    CPU *my_cpu = new CPU();

    cpu_word rom[11] = {0x41, 0x42, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x04, 0x02};

    my_cpu->load_rom(rom, 11*sizeof(cpu_word));
    my_cpu->run();
    return 0;
}
