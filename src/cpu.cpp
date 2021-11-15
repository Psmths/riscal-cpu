#include "../include/cpu.hpp"
#include "operation_exec.cpp"
#include <iostream>

#ifdef DEBUG
    #include <bitset>
#endif

CPU::CPU() {
    /* Clear registers */
    pc, sp, bp, flags = 0;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0, sizeof(cpu_word)*ADDRESS_SPACE_SIZE);
}

CPU::~CPU() {

}

void CPU::load_rom(cpu_word *rom, int rom_size) {
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

void CPU::run() {

    #ifdef DEBUG
        std::cout << "[DBG] EXECUTION START" << std::endl;
    #endif

    bool returned = false;

    while(!returned){
        cpu_word data = address_space[pc++];
        returned = execute_instruction(data);

        #ifdef DEBUG
            std::cout << "PC: " << std::bitset<16>(pc) << " (" << pc << ")" << "\tmem(" << pc << ") = " << std::bitset<16>(data) << std::endl;
            std::cout << "FLAGS: " << std::bitset<16>(flags) << std::endl;
            for (int i = 0; i < 4; i++){
                std::cout << "R" << i << ": " << std::bitset<16>(reg[i]) << " (" << reg[i] << ")" << std::endl;
            }
            std::cout << "--------------------" << std::endl;
        #endif
    }
}

bool CPU::execute_instruction(cpu_word data) {

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

    if (data >= 0x00000070 && data <= 0x0000007F) op_jump_ne(data);
    if (data >= 0x00000100 && data <= 0x000001FF) op_compare(data);
    if (data >= 0x00100000 && data <= 0x001FFFFF) op_move_lower(data);
    if (data >= 0x00200060 && data <= 0x002FFFFF) op_move_upper(data);

    return false;
}
