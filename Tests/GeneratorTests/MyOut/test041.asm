global  main
extern  printf
section .text
main:
	mov rax, 1
	neg rax
	mov [v_i], rax
	jmp L1
L0:
	mov rsi, [v_i]
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
	mov rax, [v_i]
	mov rbx, 1
	add rax, rbx
	mov [v_i], rax
L1:
	mov rax, [v_i]
	mov rbx, 3
	cmp rax, rbx
	jl L3
	xor rax, rax
	jmp L4
L3:
	mov rax, 1
L4:
	test rax, rax
	jnz L0
L2:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_i: dq 0
