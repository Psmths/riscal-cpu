#include "../include/cpu.hpp"
#include <iostream>
#include <bitset>

CPU::CPU() {
    pc = 0;
    flags = 0;

    /* Clear memory space */
    memset(address_space, 0, sizeof(cpu_byte)*ADDRESS_SPACE_SIZE);
}

CPU::~CPU() {

}

void CPU::load_rom(cpu_byte *rom, int rom_size) {
    //TODO: Check if rom too big!
    memcpy(address_space, rom, rom_size);

    #ifdef DEBUG_LOADROM
        std::cout << "---------- LOADED PROM -----------" << std::endl;
        for (int i = 0; i < rom_size; i++){
            std::cout << "mem(" << i << ") = " << std::bitset<8>(address_space[i]) << std::endl;
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
    }
}

bool CPU::execute_instruction(cpu_word data) {

    /* HALT command returns 1 */
    if (data == HLT) return true;

    /* NOP */
    if (data == NOP) op_nop();

    return false;
}

void CPU::op_nop() {
    #ifdef DEBUG
        std::cout << "[DBG] NOP" << std::endl;
    #endif
}
