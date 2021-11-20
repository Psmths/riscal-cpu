/*
    branch_test.cpp - Tests all branch instructions

    main:
    	MOVE_LOWER R15, test_fail		; Pointer to fail
    	MOVE_LOWER R14, test2		    ; Pointer to test2

    test1:
    	MOVE_LOWER R1, 25
    	MOVE_LOWER R2, 100

    	COMPARE R1, R2
    	JUMP_E test_fail				; Test jump if equal imm
    	JUMP_E R15						; Test jump if equal r
    	JUMP R14						; Test jump r
    	FAULT

    test2:
    	COMPARE R1, R2
    	JUMP_GT test_fail				; Test jump if greater imm
    	JUMP_GT R15						; Test jump if greater r
    	JUMP test3						; Test jump imm
    	FAULT

    test3:
    	COMPARE R2, R1
    	JUMP_LT test_fail				; Test jump if less imm
    	JUMP_LT R15						; Test jump if less r
    	JUMP test_succeed				; All checks passed

    test_fail:
    	HALT

    test_succeed:
    	HALT

*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <cstring>

int main() {

    RISCAL_CPU *my_cpu = new RISCAL_CPU();

    /* Adding program */
    unsigned char rom[] = {
        /* 0x00 */ 0x10, 0x0f, 0x00, 0x48, 0x10, 0x0e, 0x00, 0x24, 0x10, 0x01, 0x00, 0x19, 0x10, 0x02, 0x00, 0x64,
    	/* 0x10 */ 0x02, 0x00, 0x00, 0x12, 0x80, 0x00, 0x00, 0x48, 0x00, 0xd0, 0x00, 0x0f, 0x01, 0xf0, 0x00, 0x0e,
    	/* 0x20 */ 0x00, 0x30, 0x00, 0x00, 0x02, 0x00, 0x00, 0x12, 0x90, 0x00, 0x00, 0x48, 0x00, 0xe0, 0x00, 0x0f,
    	/* 0x30 */ 0xa0, 0x00, 0x00, 0x38, 0x00, 0x30, 0x00, 0x00, 0x02, 0x00, 0x00, 0x21, 0xa0, 0x00, 0x00, 0x48,
    	/* 0x40 */ 0x00, 0xf0, 0x00, 0x0f, 0x90, 0x00, 0x00, 0x4c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
    };

    /* Load the PROM to RISCAL */
    my_cpu->load_rom(rom, sizeof(rom));

    /* Run RISCAL */
    unsigned char* result = my_cpu->run();

    if (!result) {
        return 1;
    }

    return 0;
}
