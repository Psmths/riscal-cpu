/*
    my_adder.cpp - Example program that passes two 16-bit unsigned integers
    to the RISCAL stack, adds them, and returns them to the stack.

    outp | addr | data
     0:0 |    0 | 00 90 00 01 ; POP_WORD R1
     4:0 |    4 | 00 90 00 02 ; POP_WORD R2
     8:0 |    8 | 03 00 00 12 ; ADD R1, R2
     c:0 |    c | 00 80 00 01 ; PUSH_WORD R1
    10:0 |   10 | 00 30 00 00 ; FAULT
*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <cstring>

int main() {

    /* Two integers to add */
    uint32_t x = 500;
    uint32_t y = 200;

    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    /* Adding program */
    unsigned char rom[] = {
	/* 0x00 */ 0x00, 0x90, 0x00, 0x01, 0x00, 0x90, 0x00, 0x02, 0x03, 0x00, 0x00, 0x12, 0x00, 0x80, 0x00, 0x01,
	/* 0x10 */ 0x00, 0x10, 0x00, 0x00
    };

    /* Copy integers to the stack */
    unsigned char my_stack[8];
    memcpy(my_stack, &x, sizeof(x));
    memcpy(my_stack + sizeof(x), &y, sizeof(y));

    /* Load the PROM to RISCAL */
    my_cpu->load_rom(rom, sizeof(rom));

    /* Load the input stack */
    my_cpu->load_stack(my_stack, sizeof(my_stack));

    /* Run RISCAL */
    unsigned char* result = my_cpu->run();

    /* Print result if not FAULT status */
    if (result) {
        uint32_t result_cast;
        memcpy(&result_cast, result, sizeof(x));
        std::cout << std::dec << result_cast << std::endl;
    } else {
        return 1;
    }

    return 0;
}
