#include "../include/cpu.hpp"
#include "cpu.cpp"
#include <iostream>
#include <stdint.h>

int main() {
    /* currently very rudimetary unit test */
    CPU *my_cpu = new CPU();

    cpu_byte rom[11] = {0x41, 0x42, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x02};

    my_cpu->load_rom(rom, 11);
    my_cpu->run();
    return 0;
}
