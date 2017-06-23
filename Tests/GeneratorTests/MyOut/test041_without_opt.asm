global  main
extern  printf
section .text
main:
	mov rax, 1
	push rax
	pop rax
	neg rax
	push rax
	push v_i
	pop rax
	pop rbx
	mov [rax], rbx
	jmp L1
L0:
	mov rax, [v_i]
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
	mov rax, [v_i]
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	add rax, rbx
	push rax
	push v_i
	pop rax
	pop rbx
	mov [rax], rbx
L1:
	mov rax, [v_i]
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jl L3
	mov rax, 0
	jmp L4
L3:
	mov rax, 1
L4:
	push rax
	pop rax
	test rax, rax
	jnz L0
L2:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_i: dq 0
