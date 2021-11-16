#ifndef CPU_HPP
#define CPU_HPP

#include "structures.hpp"
#include "architecture.hpp"
#include "debugger.hpp"
#include "flags.hpp"

class RISCAL_CPU {

    private:
        /* Memory address space */
        cpu_word address_space[ADDRESS_SPACE_SIZE];

        /* Return stack space */
        char *return_stack;

        /* Four general purpose registers R0 - R3 */
        cpu_word reg[N_REGISTERS];

        /* FLAGS register */
        cpu_word flags;

        /* Program counter */
        cpu_word pc;

        /* Stack pointer */
        cpu_word sp;

        bool execute_instruction(cpu_word d);

        bool setflags(cpu_word result);

        /* Immediate commands */
        void op_nop();

        /* Single-register opcodes */
        void op_clear(cpu_word data);
        void op_increment(cpu_word data);
        void op_decrement(cpu_word data);
        void op_not(cpu_word data);
        void op_push_word(cpu_word data);
        void op_pop(cpu_word data);
        void op_jump_ne(cpu_word data);
        void op_jump_e(cpu_word data);  //TODO
        //void op_jump_gt(cpu_word data); //TODO
        //void op_jump_lt(cpu_word data); //TODO

        /* Double-register opcodes */
        void op_compare(cpu_word data);
        //void op_add(cpu_word data);
        //void op_subtract(cpu_word data);
        //void op_leftshift(cpu_word data);
        //void op_rightshift(cpu_word data);
        //void op_and(cpu_word data);
        //void op_or(cpu_word data);
        //void op_xor(cpu_word data);
        //void op_exchange(cpu_word data);
        //void op_move(cpu_word data);

        /* Data commands */
        void op_move_upper(cpu_word data);
        void op_move_lower(cpu_word data);

    public:
        /* Bare constructor */
        RISCAL_CPU();

        /* Constructor for in-memory return operations */
        RISCAL_CPU(int return_stack_size);

        ~RISCAL_CPU();
        char *run();
        void load_rom(cpu_word *rom, int rom_size);
};

#endif
