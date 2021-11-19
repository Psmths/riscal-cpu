# RISCAL Opcode Reference Sheet
---
## SPECIAL OPERATIONS
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
### REGISTER OPERATIONS
### CLEAR - Clear Register
```
CLEAR R{x} -> R{x} = 0
```

### INCREMENT - Increment Register
```
INCREMENT R{x} -> R{x} = R{x} + 1
```

### DECREMENT - Decrement Register
```
DECREMENT R{x} -> R{x} = R{x} - 1
```

### EXCHANGE - Exchange Registers
```
EXCHANGE R{x}, R{y} -> R{x} = R{y}, R{y} = R{x},
```

---
### LOGICAL OPERATIONS
### NOT
```
NOT R{x} -> R{x} = !R{x}
```

### AND
```
AND R{x}, R{y} -> R{x} = R{x} & R{y}
```

### OR
```
OR R{x}, R{y} -> R{x} = R{x} | R{y}
```

### XOR
```
XOR R{x}, R{y} -> R{x} = R{x} ^ R{y}
```

### SHIFT_LEFT
```
SHIFT_LEFT R{x}, R{y} -> R{x} = R{x} << R{y}
```

### SHIFT_RIGHT
```
SHIFT_RIGHT R{x}, R{y} -> R{x} = R{x} >> R{y}
```
## MEMORY OPERATIONS

## BRANCHING OPERATIONS
