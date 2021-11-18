/*
    load_bin_from_file.cpp

    This is a program to load a compiled binary for RISCAL into the RISCAL VM
    and execute it. You can try compiling using customasm:

        https://hlorenzi.github.io/customasm/web/

    Be cautious of the endianness of the compiled code!

    This program will print out the return stack as well.
*/

#include "../../include/cpu.hpp"
#include <iostream>
#include <fstream>

int main() {

    std::ifstream binfile;
    int binsize;

    binfile.open("rom.bin", std::ios::binary);

    binfile.seekg(0, binfile.end);
    binsize = binfile.tellg();
    binfile.seekg(0, binfile.beg);

    if (binsize < 0) return 1;

    char rom[binsize];
    binfile.read(rom, binsize);

    RISCAL_CPU *my_cpu = new RISCAL_CPU(1024);
    my_cpu->load_rom(rom, binsize);
    char* result = my_cpu->run();

    if (result) {
        std::cout << result;
    } else {
        std::cout << "Error on escape." << std::endl;
        return 1;
    }


    return 0;
}
