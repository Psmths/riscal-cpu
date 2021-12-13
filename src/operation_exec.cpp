#include "../include/cpu.hpp"

#include <cstring>

#ifdef DEBUG
    #include <iostream>
    #include <bitset>
#endif

void RISCAL_CPU::op_nop(cpu_word data) {
    #ifdef DEBUG
        std::cout << "[DBG] NOP" << std::endl;
    #endif
}

void RISCAL_CPU::op_return(cpu_word data) {
    pc = rp; /* Return to location in return pointer */
    rp = 0; /* Reset return pointer */
    #ifdef DEBUG
        std::cout << "[DBG] RETURN" << std::endl;
    #endif
}

void RISCAL_CPU::op_fault(cpu_word data) {
    error = true;
    #ifdef DEBUG
        std::cout << "[DBG] FAULT" << std::endl;
    #endif
}

/* Single-register commands */

void RISCAL_CPU::op_clear(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register = data & 0x0000000F;
    reg[op_register] = 0x00000000;

    if (reg[op_register] == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] CLEAR R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_increment(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]++;

    if (reg[op_register] == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] INCREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_decrement(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register = data & 0x0000000F;
    reg[op_register]--;

    if (reg[op_register] == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] DECREMENT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_not(cpu_word data) {

    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register = data & 0x0000000F;
    reg[op_register] = !reg[op_register];

    if (reg[op_register] == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] NOT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_push_word(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word push_data = reg[op_register];

    /* Overflow */
    if (sp > RETURN_STACK_SIZE - sizeof(cpu_word)) {
        #ifdef DEBUG
        std::cout << "[DBG] Stack overflow. Faulting." << std::endl;
        #endif
        op_fault(data);
        return;
    }


    memcpy(return_stack + sp, &push_data, sizeof(cpu_word));
    sp = sp + sizeof(cpu_word); /* Increase SP 4 for pushing word */
    #ifdef DEBUG
        std::cout << "[DBG] PUSH_WORD R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_pop_word(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;

     /* Underflow */
    if (sp < sizeof(cpu_word)) {
        #ifdef DEBUG
        std::cout << "[DBG] Stack underflow. Faulting." << std::endl;
        #endif
        op_fault(data);
        return;
    }

    sp = sp - sizeof(cpu_word); /* Decrease SP 4 for popping word */
    memcpy(&reg[op_register], return_stack + sp, sizeof(cpu_word));
    memset(return_stack + sp, 0, sizeof(cpu_word)); /* Clear popped data */
    #ifdef DEBUG
        std::cout << "[DBG] POP_WORD R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_push_byte(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_byte push_data = reg[op_register] & 0xFF;

    /* Overflow */
    if (sp > RETURN_STACK_SIZE - sizeof(cpu_byte)) {
        #ifdef DEBUG
        std::cout << "[DBG] Stack overflow. Faulting." << std::endl;
        #endif
        op_fault(data);
        return;
    }

    memcpy(return_stack + sp, &push_data, sizeof(cpu_byte));
    sp = sp + sizeof(cpu_byte); /* Increase SP 1 for pushing byte */
    #ifdef DEBUG
        std::cout << "[DBG] PUSH_BYTE R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_pop_byte(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;

    /* Underflow */
    if (sp < sizeof(cpu_byte)) {
        #ifdef DEBUG
        std::cout << "[DBG] Stack underflow. Faulting." << std::endl;
        #endif
        op_fault(data);
        return;
    }

    sp = sp - sizeof(cpu_byte); /* Decrease SP 1 for popping word */
    memcpy(&reg[op_register], return_stack + sp, sizeof(cpu_byte));
    memset(return_stack + sp, 0, sizeof(cpu_byte)); /* Clear popped data */
    #ifdef DEBUG
        std::cout << "[DBG] POP_BYTE R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_ne(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    if (!zero) pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_NE R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_e(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (zero & carry) pc = jump_location - 4;
    #ifdef DEBUG
        std::cout << "[DBG] JUMP_E R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_gt(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (!zero & !carry) pc = jump_location - 4;
    #ifdef DEBUG
        std::cout << "[DBG] JUMP_GT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_lt(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (!zero & carry) pc = jump_location - 4;
    #ifdef DEBUG
        std::cout << "[DBG] JUMP_LT R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];
    pc = jump_location - 4;
    #ifdef DEBUG
        std::cout << "[DBG] JUMP R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

void RISCAL_CPU::op_call(cpu_word data) {
    uint8_t op_register = data & 0x0000000F;
    cpu_word jump_location = reg[op_register];

    /* Set return pointer register to current program counter */
    rp = pc;

    /* Jump to call pointer */
    pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] CALL R" << std::bitset<4>(op_register) << std::endl;
    #endif
}

/* Double-register commands */

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

    if (x > y) {
        flags = flags | 0x0; // C
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

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] ADD R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_subtract(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x - y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] SUB R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_or(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x | y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] OR R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_and(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x & y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] AND R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_xor(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x ^ y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] XOR R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_shift_left(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x << y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] SHIFT_LEFT R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_shift_right(cpu_word data) {
    /* Reset FLAGS register */
    flags = 0;

    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word result = x >> y;

    reg[op_register_x] = result;

    if (result == 0) flags = flags | FLAGS_MASK_ZERO;
    if (reg[op_register_x] >> 31) flags = flags | FLAGS_MASK_SIGN;

    #ifdef DEBUG
        std::cout << "[DBG] SHIFT_RIGHT R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_exchange(cpu_word data) {
    uint8_t op_register_y = data & 0x0000000F;
    uint8_t op_register_x = (data & 0x000000F0) >> 4;

    cpu_word x = reg[op_register_x];
    cpu_word y = reg[op_register_y];

    cpu_word temp = x;

    reg[op_register_x] = y;
    reg[op_register_y] = x;

    #ifdef DEBUG
        std::cout << "[DBG] EXCHANGE R" << std::bitset<4>(op_register_x) << ", R" << std::bitset<4>(op_register_y) << std::endl;
    #endif
}

void RISCAL_CPU::op_load_word(cpu_word data) {
    uint8_t op_register_offset = data & 0x0000000F;
    uint8_t op_register_data = (data & 0x000000F0) >> 4;

    cpu_word memory_location_offset = reg[op_register_offset];
    cpu_word memory_value = 0;

    memcpy(&memory_value, &address_space[0] + memory_location_offset, sizeof(cpu_word));

    reg[op_register_data] = memory_value;

    #ifdef DEBUG
        std::cout << "[DBG] LOAD_WORD R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<4>(op_register_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_store_word(cpu_word data) {
    uint8_t op_register_offset = data & 0x0000000F;
    uint8_t op_register_data = (data & 0x000000F0) >> 4;

    cpu_word memory_location_offset = reg[op_register_offset];

    memcpy(&address_space[0] + memory_location_offset, &reg[op_register_data], sizeof(cpu_word));

    #ifdef DEBUG
        std::cout << "[DBG] STORE_WORD R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<4>(op_register_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_load_byte(cpu_word data) {
    uint8_t op_register_offset = data & 0x0000000F;
    uint8_t op_register_data = (data & 0x000000F0) >> 4;

    cpu_word memory_location_offset = reg[op_register_offset];
    cpu_word memory_value = 0;

    memcpy(&memory_value, &address_space[0] + memory_location_offset, sizeof(cpu_byte));

    reg[op_register_data] = memory_value & 0x000000FF;

    #ifdef DEBUG
        std::cout << "[DBG] LOAD_BYTE R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<4>(op_register_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_store_byte(cpu_word data) {
    uint8_t op_register_offset = data & 0x0000000F;
    uint8_t op_register_data = (data & 0x000000F0) >> 4;

    cpu_word memory_location_offset = reg[op_register_offset];

    memcpy(&address_space[0] + memory_location_offset, &reg[op_register_data], sizeof(cpu_byte));

    #ifdef DEBUG
        std::cout << "[DBG] STORE_BYTE R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<4>(op_register_offset) << std::endl;
    #endif
}

/* Data immediate commands */

void RISCAL_CPU::op_move_lower(cpu_word data) {
    uint8_t op_register = (data & 0x000F0000) >> 16;
    cpu_halfword immediate = data & 0xFFFF;
    cpu_halfword current_upper = reg[op_register] >> 16;
    cpu_word final = current_upper << 16;
    final = final + immediate;
    reg[op_register] = final;

    #ifdef DEBUG
        std::cout << "[DBG] MOVE_LOWER(imm) R" << std::bitset<4>(op_register) << ", " << std::bitset<16>(immediate) << std::endl;
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
        std::cout << "[DBG] MOVE_UPPER(imm) R" << std::bitset<4>(op_register) << ", " << std::bitset<16>(immediate) << std::endl;
    #endif
}

void RISCAL_CPU::op_load_word_imm(cpu_word data) {
    uint8_t op_register = (data & 0x000F0000) >> 16;
    cpu_halfword memory_location_offset = data & 0xFFFF;
    cpu_word memory_value;
    memcpy(&memory_value, &address_space[0] + memory_location_offset, sizeof(cpu_word));
    reg[op_register] = memory_value;

    #ifdef DEBUG
        std::cout << "[DBG] LOAD_WORD(imm) R" << std::bitset<4>(op_register) << ", @" << std::bitset<16>(memory_location_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_store_word_imm(cpu_word data) {
    uint8_t op_register_data = (data & 0x000F0000) >> 16;
    cpu_halfword memory_location_offset = data & 0xFFFF;

    memcpy(&address_space[0] + memory_location_offset, &reg[op_register_data], sizeof(cpu_word));

    #ifdef DEBUG
        std::cout << "[DBG] STORE_WORD(imm) R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<16>(memory_location_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_load_byte_imm(cpu_word data) {
    uint8_t op_register = (data & 0x000F0000) >> 16;
    cpu_halfword memory_location_offset = data & 0xFFFF;
    cpu_word memory_value;
    memcpy(&memory_value, &address_space[0] + memory_location_offset, sizeof(cpu_byte));
    reg[op_register] = memory_value & 0x000000FF;

    #ifdef DEBUG
        std::cout << "[DBG] LOAD_BYTE(imm) R" << std::bitset<4>(op_register) << ", @" << std::bitset<16>(memory_location_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_store_byte_imm(cpu_word data) {
    uint8_t op_register_data = (data & 0x000F0000) >> 16;
    cpu_halfword memory_location_offset = data & 0xFFFF;

    memcpy(&address_space[0] + memory_location_offset, &reg[op_register_data], sizeof(cpu_byte));

    #ifdef DEBUG
        std::cout << "[DBG] STORE_BYTE(imm) R" << std::bitset<4>(op_register_data) << ", R" << std::bitset<16>(memory_location_offset) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_ne_imm(cpu_word data) {
    cpu_halfword jump_location = data & 0xFFFF;
    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    if (!zero) pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_NE(imm) @" << std::bitset<16>(jump_location) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_e_imm(cpu_word data) {
    cpu_halfword jump_location = data & 0xFFFF;
    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (zero) pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_E(imm) @" << std::bitset<16>(jump_location) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_gt_imm(cpu_word data) {
    cpu_halfword jump_location = data & 0xFFFF;
    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (!zero & !carry) pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_GT(imm) @" << std::bitset<16>(jump_location) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_lt_imm(cpu_word data) {
    cpu_halfword jump_location = data & 0xFFFF;
    /* Get result of comparison */
    bool zero = flags & FLAGS_MASK_ZERO;
    bool carry = flags & FLAGS_MASK_CARRY;
    if (!zero & carry) pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP_LT(imm) @" << std::bitset<16>(jump_location) << std::endl;
    #endif
}

void RISCAL_CPU::op_jump_imm(cpu_word data) {
    cpu_halfword jump_location = data & 0xFFFF;
    pc = jump_location - 4;

    #ifdef DEBUG
        std::cout << "[DBG] JUMP(imm) @" << std::bitset<16>(jump_location) << std::endl;
    #endif
}
