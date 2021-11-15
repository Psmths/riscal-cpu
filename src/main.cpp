#include "cpu.cpp"

int main() {
    /* currently very rudimetary unit test */
    CPU *my_cpu = new CPU();

    cpu_word rom[11] = {0x00000000, 0x00000011, 0x00000021, 0x00000021,
                        0x00000021, 0x00000011, 0x00000000, 0x00000000,
                        0x00000000, 0x00000000, 0x00000001};

    my_cpu->load_rom(rom, 11*sizeof(cpu_word));
    my_cpu->run();
    return 0;
}
