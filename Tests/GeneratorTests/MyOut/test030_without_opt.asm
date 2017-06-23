global  main
extern  printf
section .text
main:
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rdi, v_3
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
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
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jl L12
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
	mov rdi, v_4
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jl L14
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
	mov rdi, v_5
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jl L16
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
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L18
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
	mov rdi, v_6
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L20
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
	mov rdi, v_7
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L22
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
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L24
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
	mov rdi, v_8
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L26
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
	mov rdi, v_9
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L28
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
	mov rax, 1
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jg L30
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
	mov rdi, v_10
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jg L32
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
	mov rdi, v_11
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jg L34
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
	v_0: db " ", 0
	v_1: db " ", 0
	v_2: db " ", 0
	v_3: db " ", 0
	v_4: db " ", 0
	v_5: db " ", 0
	v_6: db " ", 0
	v_7: db " ", 0
	v_8: db " ", 0
	v_9: db " ", 0
	v_10: db " ", 0
	v_11: db " ", 0
