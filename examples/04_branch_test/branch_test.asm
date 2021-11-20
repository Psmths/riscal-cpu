main:
	MOVE_LOWER R15, test_fail		; Pointer to fail
	MOVE_LOWER R14, test2		    ; Pointer to test2

test1:
	MOVE_LOWER R1, 25
	MOVE_LOWER R2, 100

	COMPARE R1, R2
	JUMP_E test_fail				; Test jump if equal imm
	JUMP_E R15						; Test jump if equal r
	JUMP R14						; Test jump r
	FAULT

test2:
	COMPARE R1, R2
	JUMP_GT test_fail				; Test jump if greater imm
	JUMP_GT R15						; Test jump if greater r
	JUMP_LT test3
	FAULT

test3:
	COMPARE R2, R1
	JUMP_LT test_fail				; Test jump if less imm
	JUMP_LT R15						; Test jump if less r
	JUMP_GT test_succeed			; All checks passed

test_fail:
	HALT

test_succeed:
	HALT
