# RISCAL Opcode Reference Sheet

This document serves as a reference for RISCAL's ISA. The following conventions are used:

 - `R{x}` refers to the value of Register X. In assembly, this would look like `R4`, which would resolve to the value of Register 4 at the time the command is processed.\
 - `R{x}_low8` refers to the lower 8 bits of Register X.
 - `R{x}_low16` refers to the lower 16 bits of Register X, that is, the lower half of Register X.
 - `R{x}_high16` refers to the upper 16 bits of Register X, that is, the upper half of Register X.
 - `Memory[X]` refers to the value stored in RISCAL's main memory at location X. It can be a register's value or a 16-bit immediate.
 - `Stack[X]` refers to the value stored in RISCAL's input/return stack at location X. It can be a register's value or a 16-bit immediate.
 - Special register `PC` is the Program Counter.
 - Special register `RP` is the Return Pointer. 
 - Special register `SP` is the Stack Pointer. The Stack is separate from main memory. 


## TABLE OF CONTENTS

 - [Special Commands](#special-commands)
 - [Single Register Commands](#single-register-commands)
 - [Double Register Commands](#double-register-commands)
 - [Register-Immediate Commands](#register-immediate-commands)
 - [Immediate Commands](#immediate-commands)

---
## SPECIAL COMMANDS

### NOP - No Operation
This opcode will not do anything, only increment the PC by one word (4 bytes).
```
PC = PC + 4
```

### HALT - Halt Execution
This opcode immediately halts RISCAL-VM and returns execution to the callee. The return value is the return stack.

### RETURN - Return from Call
This opcode returns from a CALL operation. It will set the program counter (PC) to the return pointer (RP) value, and clear the return pointer.
```
PC = RP
RP = 0
```

### FAULT - Trigger Fault
This opcode will immediately trigger a fault condition in RISCAL-VM, and return execution to the callee with `nullptr` as a return value to signal that a fault has occurred during operation.

---
## SINGLE REGISTER COMMANDS

### CLEAR R{x} - Clear Register
```
CLEAR R{x} -> R{x} = 0
```

### INCREMENT R{x} - Increment Register
```
INCREMENT R{x} -> R{x} = R{x} + 1
```

### DECREMENT R{x} - Decrement Register
```
DECREMENT R{x} -> R{x} = R{x} - 1
```

### NOT R{x}
```
NOT R{x} -> R{x} = !R{x}
```

### PUSH_WORD R{x}
```
SP = SP + 4
Stack[SP] = R{x}
```

### POP_WORD R{x}
```
R{x} = Stack[SP]
SP = SP - 4
```

### PUSH_BYTE R{x}
```
SP = SP + 1
Stack[SP] = R{x}
```

### POP_BYTE R{x}
```
R{x} = Stack[SP]
SP = SP - 1
```

### JUMP_NE R{x}
```
if NOT FLAGS[ZERO] then PC = R{x}
```

### JUMP_E R{x}
```
if FLAGS[ZERO] and FLAGS[CARRY] then PC = R{x}
```

### JUMP_GT R{x}
```
if NOT FLAGS[ZERO] and NOT FLAGS[CARRY] then PC = R{x}
```

### JUMP_LT R{x}
```
if NOT FLAGS[ZERO] and FLAGS[CARRY] then PC = R{x}
```

### JUMP R{x}
```
PC = R{x}
```

### CALL R{x}
```
RP = SP
PC = R{x}
```

## DOUBLE REGISTER COMMANDS

### COMPARE R{x} R{y}
```
if (R{x} == R{y}) {
        FLAGS = ZERO AND CARRY
    }

    if (R{x} < R{y}) {
        FLAGS = CARRY
    }

    if (R{x} > R{y}) {
        FLAGS = ZERO
    }
```

### ADD R{x}, R{y}
```
R{x} = R{x} + R{y}
```

### SUBTRACT R{x}, R{y}
```
R{x} = R{x} - R{y}
```

### AND R{x}, R{y}
```
R{x} = R{x} & R{y}
```

### OR R{x}, R{y}
```
R{x} = R{x} | R{y}
```

### XOR R{x}, R{y}
```
R{x} = R{x} ^ R{y}
```

### SHIFT_LEFT R{x}, R{y}
```
R{x} = R{x} << R{y}
```

### SHIFT_RIGHT R{x}, R{y}
```
R{x} = R{x} >> R{y}
```

### EXCHANGE R{x}, R{y}
```
R{x} = R{y}
R{y} = R{x}
```

### LOAD_WORD R{x}, R{y}
```
R{x} = Memory[R{y}]
```

### STORE_WORD R{x}, R{y}
```
Memory[R{y}] = R{x}
```

### LOAD_BYTE R{x}, R{y}
```
R{x}_low8 = Memory[R{y}]
```

### STORE_BYTE R{x}, R{y}
```
Memory[R{y}] = R{x}_low8
```

## REGISTER IMMEDIATE COMMANDS

### MOVE_LOWER R{x}, Imm
Moves a 16-bit immediate value to the lower 16 bits of R{x}
```
R{x}_low16 = Imm
```

### MOVE_UPPER R{x}, Imm
Moves a 16-bit immediate value to the upper 16 bits of R{x}
```
R{x}_high16 = Imm
```

### LOAD_WORD R{x}, Imm
```
R{x} = Memory[Imm]
```

### STORE_WORD R{x}, Imm
```
Memory[Imm] = R{x} 
```

### LOAD_BYTE R{x}, Imm
```
R{x}_low8 = Memory[Imm]
```

### STORE_BYTE R{x}, Imm
```
Memory[Imm] = R{x}_low8
```

## IMMEDIATE COMMANDS

### JUMP_NE Imm
```
if NOT FLAGS[ZERO] then PC = Imm
```

### JUMP_E Imm
```
if FLAGS[ZERO] and FLAGS[CARRY] then PC = Imm
```

### JUMP_GT Imm
```
if NOT FLAGS[ZERO] and NOT FLAGS[CARRY] then PC = Imm
```

### JUMP_LT Imm
```
if NOT FLAGS[ZERO] and FLAGS[CARRY] then PC = Imm
```

### JUMP Imm
```
PC = Imm
```