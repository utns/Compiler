global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L0
	xor rax, rax
	jmp L1
L0:
	mov rax, 1
L1:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_3]
	mov rbx, [v_4]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L2
	xor rax, rax
	jmp L3
L2:
	mov rax, 1
L3:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_5
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_6]
	mov rbx, [v_7]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L4
	xor rax, rax
	jmp L5
L4:
	mov rax, 1
L5:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_8]
	mov rbx, [v_9]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L6
	xor rax, rax
	jmp L7
L6:
	mov rax, 1
L7:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_10
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_11]
	mov rbx, [v_12]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L8
	xor rax, rax
	jmp L9
L8:
	mov rax, 1
L9:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_13
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_14]
	mov rbx, [v_15]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L10
	xor rax, rax
	jmp L11
L10:
	mov rax, 1
L11:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_16]
	mov rbx, [v_17]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L12
	xor rax, rax
	jmp L13
L12:
	mov rax, 1
L13:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_18
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_19]
	mov rbx, [v_20]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L14
	xor rax, rax
	jmp L15
L14:
	mov rax, 1
L15:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_21
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_22]
	mov rbx, [v_23]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L16
	xor rax, rax
	jmp L17
L16:
	mov rax, 1
L17:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_24]
	mov rbx, [v_25]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L18
	xor rax, rax
	jmp L19
L18:
	mov rax, 1
L19:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_26
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_27]
	mov rbx, [v_28]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L20
	xor rax, rax
	jmp L21
L20:
	mov rax, 1
L21:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_29
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_30]
	mov rbx, [v_31]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L22
	xor rax, rax
	jmp L23
L22:
	mov rax, 1
L23:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_32]
	mov rbx, [v_33]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L24
	xor rax, rax
	jmp L25
L24:
	mov rax, 1
L25:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_34
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_35]
	mov rbx, [v_36]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L26
	xor rax, rax
	jmp L27
L26:
	mov rax, 1
L27:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_37
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_38]
	mov rbx, [v_39]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L28
	xor rax, rax
	jmp L29
L28:
	mov rax, 1
L29:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_40]
	mov rbx, [v_41]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L30
	xor rax, rax
	jmp L31
L30:
	mov rax, 1
L31:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_42
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_43]
	mov rbx, [v_44]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L32
	xor rax, rax
	jmp L33
L32:
	mov rax, 1
L33:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_45
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_46]
	mov rbx, [v_47]
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L34
	xor rax, rax
	jmp L35
L34:
	mov rax, 1
L35:
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: dq 1.000000
	v_1: dq 2.000000
	v_2: db " ", 0
	v_3: dq 1.000000
	v_4: dq 1.000000
	v_5: db " ", 0
	v_6: dq 2.000000
	v_7: dq 1.000000
	v_8: dq 1.000000
	v_9: dq 2.000000
	v_10: db " ", 0
	v_11: dq 1.000000
	v_12: dq 1.000000
	v_13: db " ", 0
	v_14: dq 2.000000
	v_15: dq 1.000000
	v_16: dq 1.000000
	v_17: dq 2.000000
	v_18: db " ", 0
	v_19: dq 1.000000
	v_20: dq 1.000000
	v_21: db " ", 0
	v_22: dq 2.000000
	v_23: dq 1.000000
	v_24: dq 1.000000
	v_25: dq 2.000000
	v_26: db " ", 0
	v_27: dq 1.000000
	v_28: dq 1.000000
	v_29: db " ", 0
	v_30: dq 2.000000
	v_31: dq 1.000000
	v_32: dq 1.000000
	v_33: dq 2.000000
	v_34: db " ", 0
	v_35: dq 1.000000
	v_36: dq 1.000000
	v_37: db " ", 0
	v_38: dq 2.000000
	v_39: dq 1.000000
	v_40: dq 1.000000
	v_41: dq 2.000000
	v_42: db " ", 0
	v_43: dq 1.000000
	v_44: dq 1.000000
	v_45: db " ", 0
	v_46: dq 2.000000
	v_47: dq 1.000000
