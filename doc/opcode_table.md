mnemonic | opcode | opcode range | function | sets flag register
--- | --- | --- | --- | ---
NOP                 | `0000 0000 0000 0000 0000 0000 0000 0000` | `0x00000000 - 0x00000000` | No Operation | :white_check_mark: |
HALT                | `0000 0000 0000 0000 0000 0000 0000 0001` | `0x00000001 - 0x00000001` | Halt VM Execution (Return/Exit) | :white_check_mark: |
RETURN              | `0000 0000 0000 0000 0000 0000 0000 0010` | `0x00000002 - 0x00000002` | Return from CALL | :white_check_mark: |
FAULT               | `0000 0000 0000 0000 0000 0000 0000 0011` | `0x00000003 - 0x00000003` | Immediately trigger a fault condition | :white_check_mark: |
CLEAR               | `0000 0000 0000 0000 0000 0000 0001 rrrr` | `0x00000010 - 0x0000001F` | Clear register r | :white_check_mark: |
INCREMENT           | `0000 0000 0000 0000 0000 0000 0010 rrrr` | `0x00000020 - 0x0000002F` | Increment register r | :heavy_check_mark: |
DECREMENT           | `0000 0000 0000 0000 0000 0000 0011 rrrr` | `0x00000030 - 0x0000003F` | Decrement register r | :heavy_check_mark: |
NOT                 | `0000 0000 0000 0000 0000 0000 0100 rrrr` | `0x00000040 - 0x0000004F` | NOT of register r | :heavy_check_mark: |
PUSH_WORD           | `0000 0000 0000 0000 0000 0000 0101 rrrr` | `0x00000050 - 0x0000005F` | Push register r word to stack | :white_check_mark: |
POP_WORD            | `0000 0000 0000 0000 0000 0000 0110 rrrr` | `0x00000060 - 0x0000006F` | Pop word from stack to register r | :white_check_mark: |
PUSH_BYTE           | `0000 0000 0000 0000 0000 0000 0111 rrrr` | `0x00000070 - 0x0000007F` | Push register r lowest byte to stack | :white_check_mark: |
POP_BYTE            | `0000 0000 0000 0000 0000 0000 1000 rrrr` | `0x00000080 - 0x0000008F` | Pop byte from stack to register r lowest bits | :white_check_mark: |
JUMP_NE             | `0000 0000 0000 0000 0000 0000 1001 rrrr` | `0x00000090 - 0x0000009F` | Jump to location in register r if comparison was not equal | :white_check_mark: |
JUMP_E              | `0000 0000 0000 0000 0000 0000 1010 rrrr` | `0x000000A0 - 0x000000AF` | Jump to location in register r if comparison was equal | :white_check_mark: |
JUMP_GT             | `0000 0000 0000 0000 0000 0000 1011 rrrr` | `0x000000B0 - 0x000000BF` | Jump to location in register r if comparison was greater than | :white_check_mark: |
JUMP_LT             | `0000 0000 0000 0000 0000 0000 1100 rrrr` | `0x000000C0 - 0x000000CF` | Jump to location in register r if comparison was less than | :white_check_mark: |
CALL                | `0000 0000 0000 0000 0000 0000 1101 rrrr` | `0x000000D0 - 0x000000DF` | Jump to location in register r, save current PC in return register | :white_check_mark: |
COMPARE             | `0000 0000 0000 0000 0000 0001 xxxx yyyy` | `0x00000100 - 0x000001FF` | Compare register x to register y | :heavy_check_mark: |
ADD                 | `0000 0000 0000 0000 0000 0010 xxxx yyyy` | `0x00000200 - 0x000002FF` | `Rx = Rx + Ry` | :heavy_check_mark: |
SUBTRACT            | `0000 0000 0000 0000 0000 0011 xxxx yyyy` | `0x00000300 - 0x000003FF` | `Rx = Rx - Ry` | :heavy_check_mark: |
OR                  | `0000 0000 0000 0000 0000 0100 xxxx yyyy` | `0x00000400 - 0x000004FF` | `Rx = Rx | Ry` | :heavy_check_mark: |
AND                 | `0000 0000 0000 0000 0000 0101 xxxx yyyy` | `0x00000500 - 0x000005FF` | `Rx = Rx & Ry` | :heavy_check_mark: |
XOR                 | `0000 0000 0000 0000 0000 0110 xxxx yyyy` | `0x00000600 - 0x000006FF` | `Rx = Rx ^ Ry` | :heavy_check_mark: |
SHIFT_LEFT          | `0000 0000 0000 0000 0000 0111 xxxx yyyy` | `0x00000700 - 0x000007FF` | `Rx = Rx << Ry` | :heavy_check_mark: |
SHIFT_RIGHT         | `0000 0000 0000 0000 0000 1000 xxxx yyyy` | `0x00000800 - 0x000008FF` | `Rx = Rx >> Ry` | :heavy_check_mark: |
EXCHANGE            | `0000 0000 0000 0000 0000 1001 xxxx yyyy` | `0x00000900 - 0x000009FF` | `Rx = Ry, Ry = Rx` | :heavy_check_mark: |
LOAD_WORD           | `0000 0000 0000 0000 0000 1010 xxxx yyyy` | `0x00000A00 - 0x00000AFF` | `Rx <- PROM[Ry]` | :heavy_check_mark: |
STORE_WORD          | `0000 0000 0000 0000 0000 1011 xxxx yyyy` | `0x00000B00 - 0x00000BFF` | `PROM[Ry] <- Rx` | :heavy_check_mark: |
MOVE_LOWER          | `0000 0000 0001 rrrr nnnn nnnn nnnn nnnn` | `0x00100000 - 0x001FFFFF` | Move immediate value n (half-word) to register r lower half | :white_check_mark: |
MOVE_UPPER          | `0000 0000 0010 rrrr nnnn nnnn nnnn nnnn` | `0x00200060 - 0x002FFFFF` | Move immediate value n (half-word) to register r upper half | :white_check_mark: |
