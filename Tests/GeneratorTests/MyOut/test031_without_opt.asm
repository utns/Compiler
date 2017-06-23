global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	mov rax, [v_1]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L0
	mov rax, 0
	jmp L1
L0:
	mov rax, 1
L1:
	push rax
	pop rax
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
	push rax
	mov rax, [v_4]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L2
	mov rax, 0
	jmp L3
L2:
	mov rax, 1
L3:
	push rax
	pop rax
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
	push rax
	mov rax, [v_7]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	je L4
	mov rax, 0
	jmp L5
L4:
	mov rax, 1
L5:
	push rax
	pop rax
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
	push rax
	mov rax, [v_9]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L6
	mov rax, 0
	jmp L7
L6:
	mov rax, 1
L7:
	push rax
	pop rax
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
	push rax
	mov rax, [v_12]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L8
	mov rax, 0
	jmp L9
L8:
	mov rax, 1
L9:
	push rax
	pop rax
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
	push rax
	mov rax, [v_15]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jne L10
	mov rax, 0
	jmp L11
L10:
	mov rax, 1
L11:
	push rax
	pop rax
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
	push rax
	mov rax, [v_17]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L12
	mov rax, 0
	jmp L13
L12:
	mov rax, 1
L13:
	push rax
	pop rax
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
	push rax
	mov rax, [v_20]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L14
	mov rax, 0
	jmp L15
L14:
	mov rax, 1
L15:
	push rax
	pop rax
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
	push rax
	mov rax, [v_23]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jb L16
	mov rax, 0
	jmp L17
L16:
	mov rax, 1
L17:
	push rax
	pop rax
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
	push rax
	mov rax, [v_25]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L18
	mov rax, 0
	jmp L19
L18:
	mov rax, 1
L19:
	push rax
	pop rax
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
	push rax
	mov rax, [v_28]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L20
	mov rax, 0
	jmp L21
L20:
	mov rax, 1
L21:
	push rax
	pop rax
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
	push rax
	mov rax, [v_31]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jbe L22
	mov rax, 0
	jmp L23
L22:
	mov rax, 1
L23:
	push rax
	pop rax
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
	push rax
	mov rax, [v_33]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L24
	mov rax, 0
	jmp L25
L24:
	mov rax, 1
L25:
	push rax
	pop rax
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
	push rax
	mov rax, [v_36]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L26
	mov rax, 0
	jmp L27
L26:
	mov rax, 1
L27:
	push rax
	pop rax
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
	push rax
	mov rax, [v_39]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	jae L28
	mov rax, 0
	jmp L29
L28:
	mov rax, 1
L29:
	push rax
	pop rax
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
	push rax
	mov rax, [v_41]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L30
	mov rax, 0
	jmp L31
L30:
	mov rax, 1
L31:
	push rax
	pop rax
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
	push rax
	mov rax, [v_44]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L32
	mov rax, 0
	jmp L33
L32:
	mov rax, 1
L33:
	push rax
	pop rax
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
	push rax
	mov rax, [v_47]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	comisd xmm0, xmm1
	ja L34
	mov rax, 0
	jmp L35
L34:
	mov rax, 1
L35:
	push rax
	pop rax
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
