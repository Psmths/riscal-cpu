/*
    xor_cipher.cpp - Example program that passes arbitrary-length char array
    to RISCAL and encrypts it with a XOR cipher. Returns raw ciphertext.

    outp | addr | data
     0:0 |    0 | 10 03 08 00 ; MOVE_LOWER R3, 2048
     4:0 |    4 |             ; fetch_stack:
     4:0 |    4 | 00 b0 00 02 ; POP_BYTE R2
     8:0 |    8 | 0e 00 00 23 ; STORE_BYTE R2, R3
     c:0 |    c | 00 50 00 03 ; INCREMENT R3
    10:0 |   10 | 02 00 00 20 ; COMPARE R2, R0
    14:0 |   14 | 70 00 00 04 ; JUMP_NE fetch_stack
    18:0 |   18 | 10 03 08 00 ; MOVE_LOWER R3, 2048
    1c:0 |   1c | 10 04 00 10 ; MOVE_LOWER R4, 16
    20:0 |   20 | 10 06 00 60 ; MOVE_LOWER R6, my_key
    24:0 |   24 |             ; xor_enc:
    24:0 |   24 | 10 06 00 60 ; MOVE_LOWER R6, my_key
    28:0 |   28 | 00 40 00 0f ; CLEAR R15
    2c:0 |   2c |             ; xor_end_2:
    2c:0 |   2c | 0d 00 00 23 ; LOAD_BYTE R2, R3
    30:0 |   30 | 02 00 00 20 ; COMPARE R2, R0
    34:0 |   34 | 80 00 00 5c ; JUMP_E exit
    38:0 |   38 | 0d 00 00 56 ; LOAD_BYTE R5, R6
    3c:0 |   3c | 07 00 00 25 ; XOR R2, R5
    40:0 |   40 | 00 a0 00 02 ; PUSH_BYTE R2
    44:0 |   44 | 00 50 00 03 ; INCREMENT R3
    48:0 |   48 | 00 50 00 06 ; INCREMENT R6
    4c:0 |   4c | 00 50 00 0f ; INCREMENT R15
    50:0 |   50 | 02 00 00 f4 ; COMPARE R15, R4
    54:0 |   54 | 80 00 00 24 ; JUMP_E xor_enc
    58:0 |   58 | b0 00 00 2c ; JUMP xor_end_2
    5c:0 |   5c |             ; exit:
    5c:0 |   5c | 00 10 00 00 ; HALT
    60:0 |   60 |             ; my_key:
    60:0 |   60 | 59 51 b7 57 5c a1 f5 47 df fe 61 3a 34 e1 35 95 ; #d128 0x5951B7575CA1F547DFFE613A34E13595
*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <cstring>

int main() {

    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    unsigned char rom[] = {
        /* 0x00 */ 0x10, 0x03, 0x08, 0x00, 0x00, 0xb0, 0x00, 0x02, 0x0e, 0x00, 0x00, 0x23, 0x00, 0x50, 0x00, 0x03,
    	/* 0x10 */ 0x02, 0x00, 0x00, 0x20, 0x70, 0x00, 0x00, 0x04, 0x10, 0x03, 0x08, 0x00, 0x10, 0x04, 0x00, 0x10,
    	/* 0x20 */ 0x10, 0x06, 0x00, 0x60, 0x10, 0x06, 0x00, 0x60, 0x00, 0x40, 0x00, 0x0f, 0x0d, 0x00, 0x00, 0x23,
    	/* 0x30 */ 0x02, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x5c, 0x0d, 0x00, 0x00, 0x56, 0x07, 0x00, 0x00, 0x25,
    	/* 0x40 */ 0x00, 0xa0, 0x00, 0x02, 0x00, 0x50, 0x00, 0x03, 0x00, 0x50, 0x00, 0x06, 0x00, 0x50, 0x00, 0x0f,
    	/* 0x50 */ 0x02, 0x00, 0x00, 0xf4, 0x80, 0x00, 0x00, 0x24, 0xb0, 0x00, 0x00, 0x2c, 0x00, 0x10, 0x00, 0x00,
    	/* 0x60 */ 0x59, 0x51, 0xb7, 0x57, 0x5c, 0xa1, 0xf5, 0x47, 0xdf, 0xfe, 0x61, 0x3a, 0x34, 0xe1, 0x35, 0x95
    };

    /* Copy chars to the stack */
    unsigned char my_stack[] = {0x00, 0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x74, 0x65, 0x73, 0x74, 0x20, 0x6f,
	/* 0x10 */ 0x66, 0x20, 0x61, 0x20, 0x73, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x6b, 0x65, 0x79, 0x20, 0x58,
	/* 0x20 */ 0x4f, 0x52, 0x20, 0x63, 0x69, 0x70, 0x68, 0x65, 0x72};

    /* Load the PROM to RISCAL */
    my_cpu->load_rom(rom, sizeof(rom));

    /* Load the input stack */
    my_cpu->load_stack(my_stack, sizeof(my_stack));

    /* Run RISCAL */
    unsigned char* result = my_cpu->run();

    /* Print result if not FAULT status */
    if (result) {
        std::cout << std::hex << result << std::endl;
    } else {
        return 1;
    }

    return 0;
}
