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
    binsize = binfile.tellg()/sizeof(cpu_word);
    binfile.seekg(0, binfile.beg);
    cpu_word rom[binsize];
    binfile.read((char*)rom, sizeof(rom));

    RISCAL_CPU *my_cpu = new RISCAL_CPU(1024);
    my_cpu->load_rom(rom, binsize*sizeof(cpu_word));
    char* result = my_cpu->run();

    std::cout << result;

    return 0;
}
