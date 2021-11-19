#ruledef
{
    NOP                              => 0x00000000
    HALT                             => 0x00100000
    RETURN                           => 0x00200000
    FAULT                            => 0x00300000
    CLEAR R{reg}                     => 0x0040000 @ reg`4
    INCREMENT R{reg}                 => 0x0050000 @ reg`4
    DECREMENT R{reg}                 => 0x0060000 @ reg`4
    NOT R{reg}                       => 0x0070000 @ reg`4
    PUSH_WORD R{reg}                 => 0x0080000 @ reg`4
    POP_WORD R{reg}                  => 0x0090000 @ reg`4
    PUSH_BYTE R{reg}                 => 0x00A0000 @ reg`4
    POP_BYTE R{reg}                  => 0x00B0000 @ reg`4
    JUMP_NE R{reg}                   => 0x00C0000 @ reg`4
    JUMP_E R{reg}                    => 0x00D0000 @ reg`4
    JUMPT_GT R{reg}                  => 0x00E0000 @ reg`4
    JUMP_LT R{reg}                   => 0x00F0000 @ reg`4
    CALL R{reg}                      => 0x0100000 @ reg`4
    COMPARE R{reg1}, R{reg2}         => 0x020000 @ reg1`4 @ reg2`4
    ADD R{reg1}, R{reg2}             => 0x030000 @ reg1`4 @ reg2`4
    SUBTRACT R{reg1}, R{reg2}        => 0x040000 @ reg1`4 @ reg2`4
    OR R{reg1}, R{reg2}              => 0x050000 @ reg1`4 @ reg2`4
    AND R{reg1}, R{reg2}             => 0x060000 @ reg1`4 @ reg2`4
    XOR R{reg1}, R{reg2}             => 0x070000 @ reg1`4 @ reg2`4
    SHIFT_LEFT R{reg1}, R{reg2}      => 0x080000 @ reg1`4 @ reg2`4
    SHIFT_RIGHT R{reg1}, R{reg2}     => 0x090000 @ reg1`4 @ reg2`4
    EXCHANGE R{reg1}, R{reg2}        => 0x0A0000 @ reg1`4 @ reg2`4
    LOAD_WORD R{reg1}, R{reg2}       => 0x0B0000 @ reg1`4 @ reg2`4
    STORE_WORD R{reg1}, R{reg2}      => 0x0C0000 @ reg1`4 @ reg2`4
    LOAD_BYTE R{reg1}, R{reg2}       => 0x0D0000 @ reg1`4 @ reg2`4
    STORE_BYTE R{reg1}, R{reg2}      => 0x0E0000 @ reg1`4 @ reg2`4
    MOVE_LOWER R{reg}, {val}         => 0x100 @ reg`4 @ val`16
    MOVE_UPPER R{reg}, {val}         => 0x200 @ reg`4 @ val`16
    LOAD_WORD R{reg1}, @{val}        => 0x300 @ reg1`4 @ val`16
    STORE_WORD R{reg1}, @{val}       => 0x400 @ reg1`4 @ val`16
    LOAD_BYTE R{reg1}, @{val}        => 0x500 @ reg1`4 @ val`16
    STORE_BYTE R{reg1}, @{val}       => 0x600 @ reg1`4 @ val`16
	JUMP_NE {val}                    => 0x7000 @ val`16
	JUMP_E {val}                     => 0x8000 @ val`16
	JUMP_GT {val}                    => 0x9000 @ val`16
	JUMP_LT {val}                    => 0xA000 @ val`16
	JUMP {val}                       => 0xB000 @ val`16
}
