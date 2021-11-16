#include "../include/cpu.hpp"
#include "operation_exec.cpp"
#include <iostream>

#ifdef DEBUG
    #include <iomanip>
    #include <bitset>
#endif

RISCAL_CPU::RISCAL_CPU() {
    /* Clear registers */
    pc, sp, flags = 0;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0x00000000, sizeof(cpu_word)*ADDRESS_SPACE_SIZE);
    /* Allocate and clear return stack */
    return_stack =  (char*)malloc(sizeof(char) * RETURN_STACK_SIZE);
    memset(return_stack, 0x00, sizeof(char)*RETURN_STACK_SIZE);
}

RISCAL_CPU::RISCAL_CPU(int return_stack_size) {
    /* Clear registers */
    pc, sp, flags = 0;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0x00000000, sizeof(cpu_word)*ADDRESS_SPACE_SIZE);
    /* Allocate and clear return stack */
    return_stack =  (char*)malloc(sizeof(char) * return_stack_size);
    memset(return_stack, 0x00, sizeof(char)*return_stack_size);
}

RISCAL_CPU::~RISCAL_CPU() {
    free(return_stack);
}

void RISCAL_CPU::load_rom(cpu_word *rom, int rom_size) {
    //TODO: Check if rom too big!
    memcpy(address_space, rom, rom_size);

    #ifdef DEBUG
        std::cout << "---------- LOADED PROM -----------" << std::endl;
        for (int i = 0; i < rom_size/sizeof(cpu_word); i++){
            std::cout << "mem(" << i << ") = " << std::bitset<16>(address_space[i]) << std::endl;
        }
        std::cout << "-------- END LOADED PROM ---------" << std::endl;
    #endif
}

char *RISCAL_CPU::run() {

    #ifdef DEBUG
        std::cout << "[DBG] EXECUTION START" << std::endl;
    #endif

    bool returned = false;

    while(!returned){
        cpu_word data = address_space[pc++];
        returned = execute_instruction(data);

        #ifdef DEBUG
            std::cout << "PC   : " << std::bitset<32>(pc) << " (" << pc << ")" << "\tmem(" << pc << ") = " << std::bitset<16>(data) << std::endl;
            std::cout << "FLAGS: " << std::bitset<32>(flags) << std::endl;
            std::cout << "SP   : " << std::bitset<32>(sp) << std::endl;
            for (int j = 0; j < N_REGISTERS; j = j + 4){
                for (int i = 0; i < 4; i++){
                    std::cout << "R" << std::setfill('0') << std::setw(2) << i+j << ": " << std::bitset<32>(reg[i+j]) << " (" << reg[i+j] << ")\t";
                }
                std::cout << std::endl;
            }
            std::cout << "--------------------" << std::endl;
        #endif
    }

    return return_stack;
}

bool RISCAL_CPU::execute_instruction(cpu_word data) {

    /* HALT command returns 1 */
    if (data == 0x1) {
        #ifdef DEBUG
            std::cout << "[DBG] EXECUTION HALTED" << std::endl;
        #endif
        return true;
    }

    if (data == 0x0) op_nop();

    if (data >= 0x00000010 && data <= 0x0000001F) op_clear(data);
    if (data >= 0x00000020 && data <= 0x0000002F) op_increment(data);
    if (data >= 0x00000030 && data <= 0x0000003F) op_decrement(data);
    if (data >= 0x00000040 && data <= 0x0000004F) op_not(data);
    if (data >= 0x00000050 && data <= 0x0000005F) op_push_word(data);
    //if (data >= 0x00000060 && data <= 0x0000006F) op_pop(data);
    if (data >= 0x00000070 && data <= 0x0000007F) op_jump_ne(data);
    if (data >= 0x00000080 && data <= 0x0000008F) op_jump_e(data);
    //if (data >= 0x00000090 && data <= 0x0000009F) op_jump_gt(data);
    //if (data >= 0x000000A0 && data <= 0x000000AF) op_jump_lt(data);

    if (data >= 0x00000100 && data <= 0x000001FF) op_compare(data);

    if (data >= 0x00100000 && data <= 0x001FFFFF) op_move_lower(data);
    if (data >= 0x00200060 && data <= 0x002FFFFF) op_move_upper(data);

    return false;
}
