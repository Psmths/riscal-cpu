#include "../include/cpu.hpp"

#include <cstring>

#ifdef DEBUG
    #include <iostream>
    #include <iomanip>
    #include <bitset>
#endif

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

RISCAL_CPU::RISCAL_CPU() {
    /* Clear registers */
    pc, sp, flags = 0;
    /* Clear error bit */
    error = false;
    for (int i = 0; i < N_REGISTERS; i++) reg[i] = 0;
    /* Clear memory space */
    memset(address_space, 0x00, ADDRESS_SPACE_SIZE);
    /* Allocate and clear return stack */
    return_stack = new unsigned char[RETURN_STACK_SIZE];
    memset(return_stack, 0x00, sizeof(char)*RETURN_STACK_SIZE);
}

RISCAL_CPU::~RISCAL_CPU() {

}

void RISCAL_CPU::load_rom(unsigned char *rom, int rom_size) {
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
            rom_dump(rom_size);
        #endif
    }
}

void RISCAL_CPU::load_stack(unsigned char *data, int data_size) {
    /* data too large for stack space constraint, trigger FAULT */
    if (data_size > RETURN_STACK_SIZE) {
        address_space[0] = {0x03};
        error = true;
        #ifdef DEBUG
            std::cout << "ERROR: Passed stack data too large. Exiting with fault." << std::endl;
        #endif
    } else {
        memcpy(return_stack, data, data_size);
        sp = data_size;
        #ifdef DEBUG
            stack_dump();
        #endif
    }
}

unsigned char *RISCAL_CPU::run() {

    #ifdef DEBUG
        std::cout << "[DBG] EXECUTION START" << std::endl;
    #endif

    bool returned = false;

    while(!returned){
        returned = execute_instruction();

        #ifdef DEBUG
            register_dump();
            stack_dump();
        #endif

        pc = pc + sizeof(cpu_word);
    }

    /* In case RISCAL had a fault, it will return a null ptr */
    if (error) {
        return nullptr;
    }

    /* Otherwise, RISCAL will return the return stack */
    return return_stack;
}

bool RISCAL_CPU::execute_instruction() {

    cpu_word data_be;
    memcpy(&data_be, &address_space[0] + pc, sizeof(cpu_word));
    cpu_word data = swap_uint32(data_be);
    int opcode = (data >> 20) & 0xFFF;

    if (opcode == HALT) {
        #ifdef DEBUG
            std::cout << "[DBG] HALT" << std::endl;
        #endif
        return true;
    }

    if (opcode == FAULT) {
        op_fault(data);
        return true;
    }

    if(op_function_map.find(opcode) == op_function_map.end()) {
        #ifdef DEBUG
            std::cout << "[DBG] Invalid opcode! Symbol: " <<std::bitset<32>(data) << std::endl;
        #endif
        op_fault(data);
        return true;
    }else {
        op_f fp = op_function_map[opcode];
        (this->*fp)(data);
    }

    return false;
}
