#include "../include/cpu.hpp"
#include "operation_exec.cpp"

#ifdef DEBUG
    #include <iostream>
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
    if (data > 0x00000010 && data < 0x0000001F) op_clear(data);
    if (data > 0x00000020 && data < 0x0000002F) op_increment(data);
    if (data > 0x00000030 && data < 0x0000003F) op_decrement(data);

    return false;
}
