mnemonic | opcode | opcode range | function | sets flag register
--- | --- | --- | --- | ---
NOP                 | `0000 0000 0000 0000 0000 0000 0000 0000` | `0x00000000 - 0x00000000` | No Operation | :white_check_mark: |
HALT                | `0000 0000 0001 0000 0000 0000 0000 0000` | `0x00100000 - 0x00100000` | Halt VM Execution (Return/Exit) | :white_check_mark: |
RETURN              | `0000 0000 0010 0000 0000 0000 0000 0000` | `0x00200000 - 0x00200000` | Return from CALL | :white_check_mark: |
FAULT               | `0000 0000 0011 0000 0000 0000 0000 0000` | `0x00300000 - 0x00300000` | Immediately trigger a fault condition | :white_check_mark: |
CLEAR               | `0000 0000 0100 0000 0000 0000 0000 rrrr` | `0x00400000 - 0x0040000F` | Clear register r | :white_check_mark: |
INCREMENT           | `0000 0000 0101 0000 0000 0000 0000 rrrr` | `0x00500000 - 0x0050000F` | Increment register r | :heavy_check_mark: |
DECREMENT           | `0000 0000 0110 0000 0000 0000 0000 rrrr` | `0x00600000 - 0x0060000F` | Decrement register r | :heavy_check_mark: |
NOT                 | `0000 0000 0111 0000 0000 0000 0000 rrrr` | `0x00700000 - 0x0070000F` | NOT of register r | :heavy_check_mark: |
PUSH_WORD           | `0000 0000 1000 0000 0000 0000 0000 rrrr` | `0x00800000 - 0x0080000F` | Push register r word to stack | :white_check_mark: |
POP_WORD            | `0000 0000 1001 0000 0000 0000 0000 rrrr` | `0x00900000 - 0x0090000F` | Pop word from stack to register r | :white_check_mark: |
PUSH_BYTE           | `0000 0000 1010 0000 0000 0000 0000 rrrr` | `0x00A00000 - 0x00A0000F` | Push register r lowest byte to stack | :white_check_mark: |
POP_BYTE            | `0000 0000 1011 0000 0000 0000 0000 rrrr` | `0x00B00000 - 0x00B0000F` | Pop byte from stack to register r lowest bits | :white_check_mark: |
JUMP_NE             | `0000 0000 1100 0000 0000 0000 0000 rrrr` | `0x00C00000 - 0x00C0000F` | Jump to location in register r if comparison was not equal | :white_check_mark: |
JUMP_E              | `0000 0000 1101 0000 0000 0000 0000 rrrr` | `0x00D00000 - 0x00D0000F` | Jump to location in register r if comparison was equal | :white_check_mark: |
JUMP_GT             | `0000 0000 1110 0000 0000 0000 0000 rrrr` | `0x00E00000 - 0x00E0000F` | Jump to location in register r if comparison was greater than | :white_check_mark: |
JUMP_LT             | `0000 0000 1111 0000 0000 0000 0000 rrrr` | `0x00F00000 - 0x00F0000F` | Jump to location in register r if comparison was less than | :white_check_mark: |
CALL                | `0000 0001 0000 0000 0000 0000 0000 rrrr` | `0x01000000 - 0x0100000F` | Jump to location in register r, save current PC in return register | :white_check_mark: |
COMPARE             | `0000 0010 0000 0000 0000 0000 xxxx yyyy` | `0x02000000 - 0x0200000F` | Compare register x to register y | :heavy_check_mark: |
ADD                 | `0000 0011 0000 0000 0000 0000 xxxx yyyy` | `0x03000000 - 0x0300000F` | `Rx = Rx + Ry` | :heavy_check_mark: |
SUBTRACT            | `0000 0100 0000 0000 0000 0000 xxxx yyyy` | `0x04000000 - 0x0400000F` | `Rx = Rx - Ry` | :heavy_check_mark: |
OR                  | `0000 0101 0000 0000 0000 0000 xxxx yyyy` | `0x05000000 - 0x0500000F` | `Rx = Rx | Ry` | :heavy_check_mark: |
AND                 | `0000 0110 0000 0000 0000 0000 xxxx yyyy` | `0x06000000 - 0x0600000F` | `Rx = Rx & Ry` | :heavy_check_mark: |
XOR                 | `0000 0111 0000 0000 0000 0000 xxxx yyyy` | `0x07000000 - 0x0700000F` | `Rx = Rx ^ Ry` | :heavy_check_mark: |
SHIFT_LEFT          | `0000 1000 0000 0000 0000 0000 xxxx yyyy` | `0x08000000 - 0x0800000F` | `Rx = Rx << Ry` | :heavy_check_mark: |
SHIFT_RIGHT         | `0000 1001 0000 0000 0000 0000 xxxx yyyy` | `0x09000000 - 0x0900000F` | `Rx = Rx >> Ry` | :heavy_check_mark: |
EXCHANGE            | `0000 1010 0000 0000 0000 0000 xxxx yyyy` | `0x0A000000 - 0x0A00000F` | `Rx = Ry, Ry = Rx` | :heavy_check_mark: |
LOAD_WORD           | `0000 1011 0000 0000 0000 0000 xxxx yyyy` | `0x0B000000 - 0x0B00000F` | `Rx <- PROM[Ry]` | :heavy_check_mark: |
STORE_WORD          | `0000 1100 0000 0000 0000 0000 xxxx yyyy` | `0x0C000000 - 0x0C00000F` | `PROM[Ry] <- Rx` | :heavy_check_mark: |
LOAD_BYTE           | `0000 1101 0000 0000 0000 0000 xxxx yyyy` | `0x0D000000 - 0x0D00000F` | `Rx <- PROM[Ry]` | :heavy_check_mark: |
STORE_BYTE          | `0000 1110 0000 0000 0000 0000 xxxx yyyy` | `0x0E000000 - 0x0E00000F` | `PROM[Ry] <- Rx` | :heavy_check_mark: |
MOVE_LOWER          | `0001 0000 0000 rrrr nnnn nnnn nnnn nnnn` | `0x10000000 - 0x01E00000` | Move immediate value n (half-word) to register r lower half | :white_check_mark: |
MOVE_UPPER          | `0010 0000 0000 rrrr nnnn nnnn nnnn nnnn` | `0x20000000 - 0x01F00060` | Move immediate value n (half-word) to register r upper half | :white_check_mark: |
