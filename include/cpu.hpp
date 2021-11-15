#ifndef CPU_HPP
#define CPU_HPP

#include "structures.hpp"
#include "architecture.hpp"
#include "opcodes.hpp"
#include "debugger.hpp"

class CPU {

    private:
        /* Memory address space */
        cpu_byte address_space[ADDRESS_SPACE_SIZE];

        /* Four general purpose registers R0 - R3 */
        cpu_word reg [N_REGISTERS];

        /* FLAGS register */
        cpu_word flags;

        /* Program counter */
        cpu_word pc;

        /* Stack pointer */
        cpu_word sp;

        /* Base pointer */
        cpu_word bp;

        bool execute_instruction(cpu_word d);

        void op_nop();

    public:
        CPU();
        ~CPU();
        void run();
        void load_rom(cpu_byte *rom, int rom_size);
};

#endif
