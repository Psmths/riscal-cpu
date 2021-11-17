#ruledef
{
    NOP                              => 0x00000000
    HALT                             => 0x00000001
    RETURN                           => 0x00000002
    CLEAR R{reg}                     => 0x0000001 @ reg`4
    INCREMENT R{reg}                 => 0x0000002 @ reg`4
    DECREMENT R{reg}                 => 0x0000003 @ reg`4
    NOT R{reg}                       => 0x0000004 @ reg`4
    PUSH_WORD R{reg}                 => 0x0000005 @ reg`4
    POP_WORD R{reg}                  => 0x0000006 @ reg`4
    PUSH_BYTE R{reg}                 => 0x0000007 @ reg`4
    POP_BYTE R{reg}                  => 0x0000008 @ reg`4
    JUMP_NE R{reg}                   => 0x0000009 @ reg`4
    JUMP_E R{reg}                    => 0x000000A @ reg`4
    JUMPT_GT R{reg}                  => 0x000000B @ reg`4
    JUMP_LT R{reg}                   => 0x000000C @ reg`4
    CALL R{reg}                      => 0x000000D @ reg`4
    COMPARE R{reg1}, R{reg2}         => 0x000001 @ reg1`4 @ reg2`4
    ADD R{reg1}, R{reg2}             => 0x000002 @ reg1`4 @ reg2`4
    SUBTRACT R{reg1}, R{reg2}        => 0x000003 @ reg1`4 @ reg2`4
    OR R{reg1}, R{reg2}              => 0x000004 @ reg1`4 @ reg2`4
    AND R{reg1}, R{reg2}             => 0x000005 @ reg1`4 @ reg2`4
    XOR R{reg1}, R{reg2}             => 0x000006 @ reg1`4 @ reg2`4
    SHIFT_LEFT R{reg1}, R{reg2}      => 0x000007 @ reg1`4 @ reg2`4
    SHIFT_RIGHT R{reg1}, R{reg2}     => 0x000008 @ reg1`4 @ reg2`4
    EXCHANGE R{reg1}, R{reg2}        => 0x000009 @ reg1`4 @ reg2`4
    LOAD_WORD R{reg1}, R{reg2}       => 0x00000A @ reg1`4 @ reg2`4
    STORE_WORD R{reg1}, R{reg2}      => 0x00000B @ reg1`4 @ reg2`4
    MOVE_LOWER R{reg}, {val}         => 0x001 @ reg`4 @ val`16
    MOVE_UPPER R{reg}, {val}         => 0x002 @ reg`4 @ val`16
}
