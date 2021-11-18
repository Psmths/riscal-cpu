#include "../include/cpu.hpp"

#include <cstring>

#ifdef DEBUG
    #include <iostream>
    #include <iomanip>
    #include <bitset>
#endif

RISCAL_CPU::RISCAL_CPU() {
    /* Clear registers */
    pc, sp, flags = 0;
    /* Clear error bit */
    error = false;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0x00, ADDRESS_SPACE_SIZE);
    /* Allocate and clear return stack */
    return_stack = new char[RETURN_STACK_SIZE];
    memset(return_stack, 0x00, sizeof(char)*RETURN_STACK_SIZE);
}

RISCAL_CPU::RISCAL_CPU(int return_stack_size) {
    /* Clear registers */
    pc, sp, flags = 0;
    /* Clear error bit */
    error = false;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0x00, ADDRESS_SPACE_SIZE);
    /* Allocate and clear return stack */
    return_stack = new char[return_stack_size];
    memset(return_stack, 0x00, sizeof(char)*return_stack_size);
}

RISCAL_CPU::~RISCAL_CPU() {

}

void RISCAL_CPU::load_rom(char *rom, int rom_size) {
    /* ROM too large for address space constraint, trigger FAULT */
    if (rom_size > ADDRESS_SPACE_SIZE) {
        address_space[0] = {0x03};
        error = true;
        #ifdef DEBUG
            std::cout << "ERROR: PROM too large. Exiting with fault." << std::endl;
        #endif
    } else {
        memcpy(address_space, rom, rom_size);
        #ifdef DEBUG
            std::cout << "---------- LOADED PROM -----------" << std::endl;
            for (int i = 0; i < rom_size; i++){
                std::cout << "mem(" << i << ") = " << std::bitset<8>(address_space[i]) << std::endl;
            }
            std::cout << "-------- END LOADED PROM ---------" << std::endl;
        #endif
    }
}

char *RISCAL_CPU::run() {

    #ifdef DEBUG
        std::cout << "[DBG] EXECUTION START" << std::endl;
    #endif

    bool returned = false;

    while(!returned){
        cpu_word data;
        memcpy(&data, address_space + pc, sizeof(cpu_word));

        returned = execute_instruction(data);

        #ifdef DEBUG
            std::cout << "PC   : " << std::bitset<32>(pc) << " (" << pc << ")";
            std::cout << "\tFLAGS: " << std::bitset<32>(flags) << " (" << flags << ")";
            std::cout << "\tSP   : " << std::bitset<32>(sp) << " (" << sp << ")";
            std::cout << "\tRP   : " << std::bitset<32>(rp) << " (" << rp << ")" << std::endl;
            for (int j = 0; j < N_REGISTERS; j++){
                if (reg[j] != 0){
                    std::cout << "R" << j << ": " << std::bitset<32>(reg[j]) << " (" << (0xFFFFFFFF & reg[j]) << ")" << std::endl;
                }
            }
            /* Hex dump of return stack */
            if (sp > 0) {
                std::cout << "=============================== RETURN STACK DUMP ================================" << std::endl;

                for (int x = 0; x < (sp / 16) + 1; x++){
                    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(4) << x*16 << " | ";
                    for (int y = 0; y < 16; y ++){
                        if (y % 4 == 0 & y > 0) std::cout << " ";
                        std::cout << std::hex << std::setw(2) << (0xFF & return_stack[y+x*16]) << " ";
                    }
                    std::cout << " | ";
                    for (int y = 0; y < 16; y ++){
                        if (y % 4 == 0 & y > 0) std::cout << " ";
                        if (return_stack[y+x*16] > 32 & return_stack[y+x*16] < 126){
                            std::cout << return_stack[y+x*16];
                        } else {
                            std::cout << ".";
                        }
                    }
                    std::cout << std::endl << std::dec;
                }
                std::cout << "==================================================================================" << std::endl;
            }
            std::cout << "--------------------" << std::endl;
        #endif

        pc = pc + 4;
    }

    /* In case RISCAL had a fault, it will return a null ptr */
    if (error) {
        return nullptr;
    }

    /* Otherwise, RISCAL will return the return stack */
    return return_stack;
}

bool RISCAL_CPU::execute_instruction(cpu_word data) {

    /* HALT command returns 1 */
    if (data == 0x1) {
        #ifdef DEBUG
            std::cout << "[DBG] HALT" << std::endl;
        #endif
        return true;
    }

    if (data == 0x0) op_nop();
    if (data == 0x2) op_return();
    if (data == 0x3) {
        op_fault();
        return true;
    }

    if (data >= 0x00000010 && data <= 0x0000001F) op_clear(data);
    if (data >= 0x00000020 && data <= 0x0000002F) op_increment(data);
    if (data >= 0x00000030 && data <= 0x0000003F) op_decrement(data);
    if (data >= 0x00000040 && data <= 0x0000004F) op_not(data);
    if (data >= 0x00000050 && data <= 0x0000005F) op_push_word(data);
    if (data >= 0x00000060 && data <= 0x0000006F) op_pop_word(data);
    //if (data >= 0x00000070 && data <= 0x0000007F) op_push_byte(data);
    //if (data >= 0x00000080 && data <= 0x0000008F) op_pop_byte(data);
    if (data >= 0x00000090 && data <= 0x0000009F) op_jump_ne(data);
    if (data >= 0x000000A0 && data <= 0x000000AF) op_jump_e(data);
    //if (data >= 0x000000B0 && data <= 0x000000BF) op_jump_gt(data);
    //if (data >= 0x000000C0 && data <= 0x000000CF) op_jump_lt(data);
    if (data >= 0x000000D0 && data <= 0x000000DF) op_call(data);

    if (data >= 0x00000100 && data <= 0x000001FF) op_compare(data);
    if (data >= 0x00000200 && data <= 0x000002FF) op_add(data);
    if (data >= 0x00000300 && data <= 0x000003FF) op_subtract(data);
    if (data >= 0x00000400 && data <= 0x000004FF) op_or(data);
    if (data >= 0x00000500 && data <= 0x000005FF) op_and(data);
    if (data >= 0x00000600 && data <= 0x000006FF) op_xor(data);
    if (data >= 0x00000700 && data <= 0x000007FF) op_shift_left(data);
    if (data >= 0x00000800 && data <= 0x000008FF) op_shift_right(data);
    if (data >= 0x00000900 && data <= 0x000009FF) op_exchange(data);
    if (data >= 0x00000A00 && data <= 0x00000AFF) op_load_word(data);
    if (data >= 0x00000B00 && data <= 0x00000BFF) op_store_word(data);

    if (data >= 0x00100000 && data <= 0x001FFFFF) op_move_lower(data);
    if (data >= 0x00200060 && data <= 0x002FFFFF) op_move_upper(data);

    return false;
}
