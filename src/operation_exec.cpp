#ifdef DEBUG
    #include <iostream>
#endif

void CPU::op_nop() {
    #ifdef DEBUG
        std::cout << "[DBG] NOP" << std::endl;
    #endif
}

void CPU::op_clear(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register] = 0;

    #ifdef DEBUG
        std::cout << "[DBG] CLEAR R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void CPU::op_increment(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]++;

    #ifdef DEBUG
        std::cout << "[DBG] INCREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void CPU::op_decrement(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]--;

    #ifdef DEBUG
        std::cout << "[DBG] DECREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}
