mnemonic | opcode | opcode range | function
--- | --- | --- | ---
NOP  | `0000 0000 0000 0000 0000 0000 0000 0000` | `0x00000000 - 0x00000000` | No Operation |
HALT  | `0000 0000 0000 0000 0000 0000 0000 0001` | `0x00000001 - 0x00000001` | Halt VM Execution (Return/Exit) |
CLEAR | `0000 0000 0000 0000 0000 0000 0001 rrrr` | `0x00000010 - 0x0000001F` | Clear register r |
INCREMENT | `0000 0000 0000 0000 0000 0000 0010 rrrr` | `0x00000020 - 0x0000002F` | Increment register r |
DECREMENT | `0000 0000 0000 0000 0000 0000 0011 rrrr` | `0x00000030 - 0x0000003F` | Decrement register r |
NOT | `0000 0000 0000 0000 0000 0000 0100 rrrr` | `0x00000040 - 0x0000004F` | NOT of register r |
PUSH | `0000 0000 0000 0000 0000 0000 0101 rrrr` | `0x00000050 - 0x0000005F` | Push register r to stack |
POP | `0000 0000 0000 0000 0000 0000 0110 rrrr` | `0x00000060 - 0x0000006F` | Pop from stack to register r |
JUMP_NE | `0000 0000 0000 0000 0000 0000 0111 rrrr` | `0x00000070 - 0x0000007F` | Jump to location in register r if comparison was not equal |
COMPARE | `0000 0000 0000 0000 0000 0001 yyyy xxxx` | `0x00000100 - 0x000001FF` | Compare register x to register y |
MOVE_LOWER | `0000 0000 0001 rrrr nnnn nnnn nnnn nnnn` | `0x00100000 - 0x001FFFFF` | Move immediate value n (half-word) to register r lower half |
MOVE_UPPER | `0000 0000 0010 rrrr nnnn nnnn nnnn nnnn` | `0x00200060 - 0x002FFFFF` | Move immediate value n (half-word) to register r upper half |
