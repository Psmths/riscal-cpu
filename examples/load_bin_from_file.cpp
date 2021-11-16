/*
    load_bin_from_file.cpp
    This is a program to load a compiled binary for RISCAL into the RISCAL VM
    and execute it. You can try compiling using customasm:

        https://hlorenzi.github.io/customasm/web/

    Be cautious of the endianness of the compiled code!
*/

#include "../src/cpu.cpp"
#include <fstream>
#include <vector>

int main() {

    std::ifstream fileBinToRead;
    int mcsize;

    fileBinToRead.open("output.bin", std::ios::binary);

    if(fileBinToRead.is_open()) {
        fileBinToRead.seekg(0, fileBinToRead.end);
        mcsize = fileBinToRead.tellg()/sizeof(cpu_word);
        fileBinToRead.seekg(0, fileBinToRead.beg);
    }

    #ifdef DEBUG
        std::cout << "Loaded PROM Size (words): " << mcsize << std::endl;
    #endif

    cpu_word rom[mcsize];
    fileBinToRead.read((char*)rom, sizeof(rom));

    RISCAL_CPU *my_cpu = new RISCAL_CPU();
    my_cpu->load_rom(rom, mcsize*sizeof(cpu_word));
    my_cpu->run();
    return 0;
}

// Swap File Endinness : xxd -e -g4 test.bin | xxd -r > output.bin
