#include "cpu.cpp"

int main() {
    /* currently very rudimetary unit test */
    CPU *my_cpu = new CPU();

    /* Simple loop program

    MOVE_LOWER R0011, 0000000000000010
    MOVE_LOWER R0001, 0000000000001111
    INCREMENT R0000
    COMPARE R0000, R0001
    JUMP_NE R0011
    HALT

    */
    cpu_word rom[11] = {0x00130002, 0x0011000F, 0x00000020, 0x00000110,
                        0x00000073, 0x00000001};

    my_cpu->load_rom(rom, 11*sizeof(cpu_word));
    my_cpu->run();
    return 0;
}
