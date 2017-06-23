global  main
extern  printf
section .text
main:
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
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
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
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
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
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
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
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
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
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
	mov rdi, v_3
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
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
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
	jl L12
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
	mov rdi, v_4
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
	jl L14
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
	mov rdi, v_5
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
	jl L16
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
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
	jle L18
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
	mov rdi, v_6
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
	jle L20
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
	mov rdi, v_7
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
	jle L22
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
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
	jge L24
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
	mov rdi, v_8
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
	jge L26
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
	mov rdi, v_9
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
	jge L28
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
	mov rax, 1
	mov rbx, 2
	cmp rax, rbx
	jg L30
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
	mov rdi, v_10
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	mov rbx, 1
	cmp rax, rbx
	jg L32
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
	mov rdi, v_11
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 2
	mov rbx, 1
	cmp rax, rbx
	jg L34
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
