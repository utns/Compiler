global  main
extern  printf
section .text
main:
	xor rax, rax
	push rax
	xor rax, rax
	mov rbx, rax
	pop rax
	test rax, rax
	jnz L0
	test rbx, rbx
	jnz L0
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
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rbx, 1
	test rax, rax
	jnz L2
	test rbx, rbx
	jnz L2
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
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, 1
	push rax
	xor rax, rax
	mov rbx, rax
	pop rax
	test rax, rax
	jnz L4
	test rbx, rbx
	jnz L4
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
	mov rbx, 1
	test rax, rax
	jnz L6
	test rbx, rbx
	jnz L6
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
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
