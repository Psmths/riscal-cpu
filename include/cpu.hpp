#ifndef CPU_HPP
#define CPU_HPP

#include "structures.hpp"
#include "architecture.hpp"
#include "debugger.hpp"
#include "flags.hpp"
#include "opcode_lut.hpp"

#include <map>

class RISCAL_CPU {

    private:
        /* Memory address space */
        unsigned char address_space[ADDRESS_SPACE_SIZE];

        /* Return stack space */
        unsigned char *return_stack;

        /* Four general purpose registers R0 - R3 */
        cpu_word reg[N_REGISTERS];

        /* FLAGS register */
        cpu_word flags;

        /* Program counter */
        cpu_word pc;

        /* Stack pointer */
        cpu_word sp;

        /* Return pointer */
        cpu_word rp;

        /* Error bit */
        bool error;

        bool execute_instruction();

        void register_dump();
        void rom_dump(int rom_size);
        void stack_dump();

        bool setflags(cpu_word result);

        /* Immediate commands */
        void op_nop(cpu_word data);
        void op_return(cpu_word data);
        void op_fault(cpu_word data);

        /* Single-register opcodes */
        void op_clear(cpu_word data);
        void op_increment(cpu_word data);
        void op_decrement(cpu_word data);
        void op_not(cpu_word data);
        void op_push_word(cpu_word data);
        void op_pop_word(cpu_word data);
        void op_push_byte(cpu_word data);
        void op_pop_byte(cpu_word data);
        void op_jump_ne(cpu_word data);
        void op_jump_e(cpu_word data);
        //void op_jump_gt(cpu_word data);
        //void op_jump_lt(cpu_word data);
        void op_call(cpu_word data);

        /* Double-register opcodes */
        void op_compare(cpu_word data);
        void op_add(cpu_word data);
        void op_subtract(cpu_word data);
        void op_or(cpu_word data);
        void op_and(cpu_word data);
        void op_xor(cpu_word data);
        void op_shift_left(cpu_word data);
        void op_shift_right(cpu_word data);
        void op_exchange(cpu_word data);
        void op_load_word(cpu_word data);
        void op_store_word(cpu_word data);
        void op_load_byte(cpu_word data);
        void op_store_byte(cpu_word data);

        /* Data immediate commands */
        void op_move_upper(cpu_word data);
        void op_move_lower(cpu_word data);
        void op_load_word_imm(cpu_word data);
        //void op_store_word_imm(cpu_word data);
        void op_load_byte_imm(cpu_word data);
        //void op_store_byte_imm(cpu_word data);
        void op_jump_ne_imm(cpu_word data);

        typedef void (RISCAL_CPU::*op_f)(cpu_word data);

        std::map <int, op_f> op_function_map = {
            {NOP, &RISCAL_CPU::op_nop},
            {RETURN, &RISCAL_CPU::op_return},
            {CLEAR, &RISCAL_CPU::op_clear},
            {INCREMENT, &RISCAL_CPU::op_increment},
            {DECREMENT, &RISCAL_CPU::op_decrement},
            {NOT, &RISCAL_CPU::op_not},
            {PUSH_WORD, &RISCAL_CPU::op_push_word},
            {POP_WORD, &RISCAL_CPU::op_pop_word},
            {PUSH_BYTE, &RISCAL_CPU::op_push_byte},
            {POP_BYTE, &RISCAL_CPU::op_pop_byte},
            {JUMP_NE, &RISCAL_CPU::op_jump_ne},
            {JUMP_E, &RISCAL_CPU::op_jump_e},
            {CALL, &RISCAL_CPU::op_call},
            {COMPARE, &RISCAL_CPU::op_compare},
            {ADD, &RISCAL_CPU::op_add},
            {SUBTRACT, &RISCAL_CPU::op_subtract},
            {OR, &RISCAL_CPU::op_or},
            {AND, &RISCAL_CPU::op_and},
            {XOR, &RISCAL_CPU::op_xor},
            {SHIFT_LEFT, &RISCAL_CPU::op_shift_left},
            {SHIFT_RIGHT, &RISCAL_CPU::op_shift_right},
            {EXCHANGE, &RISCAL_CPU::op_exchange},
            {LOAD_WORD, &RISCAL_CPU::op_load_word},
            {STORE_WORD, &RISCAL_CPU::op_store_word},
            {LOAD_BYTE, &RISCAL_CPU::op_load_byte},
            {STORE_BYTE, &RISCAL_CPU::op_store_byte},
            {MOVE_LOWER, &RISCAL_CPU::op_move_lower},
            {MOVE_UPPER, &RISCAL_CPU::op_move_upper},
            {LOAD_WORD_IMM, &RISCAL_CPU::op_load_word_imm},
            {LOAD_BYTE_IMM, &RISCAL_CPU::op_load_byte_imm},
            {JUMP_NE_IMM, &RISCAL_CPU::op_jump_ne_imm}
        };

    public:
        RISCAL_CPU();
        ~RISCAL_CPU();
        unsigned char *run();
        void load_rom(unsigned char *rom, int rom_size);
        void load_stack(unsigned char *data, int data_size);
};

#endif
