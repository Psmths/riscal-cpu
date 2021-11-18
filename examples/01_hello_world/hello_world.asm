main:
	MOVE_LOWER R1, mystring		; Get pointer to string
loop:
	LOAD_BYTE R2, R1			; Get data at pointer
	PUSH_BYTE R2				; Push data to return stack
	INCREMENT R1				; Increment pointer
	COMPARE R2, R0				; Check if end of string
	JUMP_NE loop
	HALT						; Exit RISCAL
mystring:
	#d "Hello World!", 0x0a, 0x00
