MOVE_LOWER R3, 2048			; Address to store input

fetch_stack:
	POP_BYTE R2				; Data from input stack
	STORE_BYTE R2, R3		; Send byte to storage
	INCREMENT R3			; Increment counter
	COMPARE R2, R0			; Is is the end of the string?
	JUMP_NE fetch_stack

MOVE_LOWER R3, 2048			; Reset data pointer
MOVE_LOWER R4, 16			; XOR key size
MOVE_LOWER R6, my_key		; XOR key pointer

xor_enc:
	MOVE_LOWER R6, my_key	; XOR key pointer
	CLEAR R15				; COR key counter
xor_end_2:
	LOAD_BYTE R2, R3		; Get data char
	COMPARE R2, R0			; End of char?
	JUMP_E exit				; If so, exit
	LOAD_BYTE R5, R6		; Get XOR key char
	XOR R2, R5				; Perform XOR
	PUSH_BYTE R2			; Push result to return stack
	INCREMENT R3			; Increment data pointer
	INCREMENT R6			; Increment XOR key pointer
	INCREMENT R15			; Increment XOR key counter
	COMPARE R15, R4			; End of key? =
	JUMP_E xor_enc			; If so, reset key pointer
	JUMP xor_end_2
exit:
	HALT
my_key:
	#d128 0x5951B7575CA1F547DFFE613A34E13595
