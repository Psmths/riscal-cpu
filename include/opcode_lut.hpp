#ifndef OPCODES_LUT_HPP
#define OPCODES_LUT_HPP

#define NOP 0x000
#define HALT 0x001
#define RETURN 0x002
#define FAULT 0x003
#define CLEAR 0x004
#define INCREMENT 0x005
#define DECREMENT 0x006
#define NOT 0x007
#define PUSH_WORD 0x008
#define POP_WORD 0x009
#define PUSH_BYTE 0x00A
#define POP_BYTE 0x00B
#define JUMP_NE 0x00C
#define JUMP_E 0x00D
#define JUMP_GT 0x00E
#define JUMP_LT 0x00F
#define CALL 0x010
#define COMPARE 0x020
#define ADD 0x030
#define SUBTRACT 0x040
#define OR 0x050
#define AND 0x060
#define XOR 0x070
#define SHIFT_LEFT 0x080
#define SHIFT_RIGHT 0x090
#define EXCHANGE 0x0A0
#define LOAD_WORD 0x0B0
#define STORE_WORD 0x0C0
#define LOAD_BYTE 0x0D0
#define STORE_BYTE 0x0E0
#define MOVE_LOWER 0x100
#define MOVE_UPPER 0x200
#define LOAD_WORD_IMM 0x300
#define STORE_WORD_IMM 0x400
#define LOAD_BYTE_IMM 0x500
#define STORE_BYTE_IMM 0x600
#define JUMP_NE_IMM 0x700
#define JUMP_E_IMM 0x800
#define JUMP_GT_IMM  0x900
#define JUMP_LT_IMM  0xA00
#define JUMP_IMM  0xB00

#endif
