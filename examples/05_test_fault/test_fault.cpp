/*
    test_fault.cpp - test RISCAL fault state

    main:
    	FAULT

*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <cstring>

int main() {

    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    unsigned char rom[] = {
        /* 0x0 */ 0x00, 0x30, 0x00, 0x00
    };

    /* Load the PROM to RISCAL */
    my_cpu->load_rom(rom, sizeof(rom));

    /* Run RISCAL */
    unsigned char* result = my_cpu->run();

    if (result) {
        return 1;
    }

    return 0;
}
