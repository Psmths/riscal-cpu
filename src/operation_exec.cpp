#include <iostream>
#include <iomanip>

void RISCAL_CPU::op_nop() {
    #ifdef DEBUG
        std::cout << "[DBG] NOP" << std::endl;
    #endif
}

void RISCAL_CPU::op_clear(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register] = 0;

    #ifdef DEBUG
        std::cout << "[DBG] CLEAR R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_increment(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]++;

    #ifdef DEBUG
        std::cout << "[DBG] INCREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_decrement(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]--;

    #ifdef DEBUG
        std::cout << "[DBG] DECREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_not(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    reg[op_register] = !reg[op_register];

    #ifdef DEBUG
        std::cout << "[DBG] DECREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_push_word(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word push_data = reg[op_register];
    memcpy(return_stack + sp, &push_data, sizeof(cpu_word));
    sp = sp + sizeof(cpu_word); /* Increase SP 4 for pushing word */
    #ifdef DEBUG
        std::cout << "[DBG] PUSH R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_ne(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register] / 4;

    /* Get result of comparison - NE */
    bool is_e = flags & FLAGS_MASK_ZERO;
    if (!is_e) pc = jump_location;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_NE R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_e(cpu_word data) {

    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Get result of comparison - E */
    bool is_e = flags & FLAGS_MASK_ZERO;
    if (is_e) pc = jump_location;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_E R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_compare(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    /* EQUAL -> Z = 1, C = 0 */
    /* LESSTHAN -> Z = 0, C = 1 */
    /* GREATERTHAN -> Z = 0, C = 0 */

    if (x == y) {
        flags = flags | 0x1; // Z
        flags = flags | 0x2; // C
    }

    if (x < y) {
        flags = flags | 0x2; // C
    }

    #ifdef DEBUG
        std::cout << "[DBG] COMPARE R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_add(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x + y;

    reg[op_register_x] = result;

    #ifdef DEBUG
        std::cout << "[DBG] ADD R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_move_lower(cpu_word data) {

    uint8_t op_register = (data & 0x000F0000) >> 16;
    cpu_halfword immediate = data & 0xFFFF;
    cpu_halfword current_upper = reg[op_register] >> 16;
    cpu_word final = current_upper << 16;
    final = final + immediate;
    reg[op_register] = final;

    #ifdef DEBUG
        std::cout << "[DBG] MOVE_LOWER R" << std::bitset<4>(op_register) << ", " << std::bitset<16>(immediate) << std::endl;
    #endif
}

void RISCAL_CPU::op_move_upper(cpu_word data) {

    uint8_t op_register = (data & 0x000F0000) >> 16;
    cpu_halfword immediate = (data & 0xFFFF);
    cpu_halfword current_lower = reg[op_register] & 0xFFFF;
    cpu_word final = immediate << 16;
    final = final + current_lower;
    //TODO: Fix this, it will clear the lower halfword
    reg[op_register] = final;

    #ifdef DEBUG
        std::cout << "[DBG] MOVE_UPPER R" << std::bitset<4>(op_register) << ", " << std::bitset<16>(immediate) << std::endl;
    #endif
}
