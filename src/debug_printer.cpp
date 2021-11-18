#include "../include/cpu.hpp"

#ifdef DEBUG
    #include <iostream>
    #include <iomanip>
    #include <bitset>
#endif

void RISCAL_CPU::register_dump() {
    #ifdef DEBUG
        std::cout << "================================= REGISTER DUMP ==================================" << std::endl;

        std::cout << "PC   : " << std::bitset<32>(pc) << " (" << pc << ")";
        std::cout << "\tFLAGS: " << std::bitset<32>(flags) << " (" << flags << ")";
        std::cout << "\tSP   : " << std::bitset<32>(sp) << " (" << sp << ")";
        std::cout << "\tRP   : " << std::bitset<32>(rp) << " (" << rp << ")" << std::endl;
        for (int j = 0; j < N_REGISTERS; j++){
            if (reg[j] != 0){
                std::cout << "R" << j << ": " << std::bitset<32>(reg[j]) << " (" << (0xFFFFFFFF & reg[j]) << ")" << std::endl;
            }
        }
        std::cout << "==================================================================================" << std::endl;
    #endif
}

void RISCAL_CPU::rom_dump(int rom_size) {
    #ifdef DEBUG
        std::cout << "=================================== PROM DUMP ====================================" << std::endl;
        for (int i = 0; i < rom_size; i++){
            std::cout << "mem(" << i << ") = " << std::bitset<8>(address_space[i]) << std::endl;
        }
        std::cout << "==================================================================================" << std::endl;
    #endif
}

void RISCAL_CPU::stack_dump() {
    #ifdef DEBUG
        if (sp > 0) {
            std::cout << "=============================== RETURN STACK DUMP ================================" << std::endl;

            for (int x = 0; x < (sp / 16) + 1; x++){
                std::cout << "0x" << std::hex << std::setfill('0') << std::setw(4) << x*16 << " | ";
                for (int y = 0; y < 16; y ++){
                    if ((y % 4 == 0) & y > 0) std::cout << " ";
                    std::cout << std::hex << std::setw(2) << (0xFF & return_stack[y+x*16]) << " ";
                }
                std::cout << " | ";
                for (int y = 0; y < 16; y ++){
                    if ((y % 4 == 0) & y > 0) std::cout << " ";
                    if (return_stack[y+x*16] > 32 & return_stack[y+x*16] < 126){
                        std::cout << return_stack[y+x*16];
                    } else {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl << std::dec;
            }
            std::cout << "==================================================================================" << std::endl;
        }
    #endif
}
