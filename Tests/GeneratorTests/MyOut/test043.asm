global  main
extern  printf
section .text
main:
	xor rax, rax
	mov [v_i], rax
	jmp L1
L0:
	mov rax, [v_i]
	mov rbx, 1
	add rax, rbx
	mov [v_i], rax
	mov rax, [v_i]
	mov rbx, 9
	cmp rax, rbx
	je L3
	xor rax, rax
	jmp L4
L3:
	mov rax, 1
L4:
	test rax, rax
	jz L5
	jmp L2
L5:
	mov rax, [v_i]
	mov rbx, 2
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
	mov rbx, 1
	cmp rax, rbx
	je L7
	xor rax, rax
	jmp L8
L7:
	mov rax, 1
L8:
	test rax, rax
	jz L9
	jmp L1
L9:
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
L1:
	mov rax, [v_i]
	mov rbx, 10
	cmp rax, rbx
	jle L11
	xor rax, rax
	jmp L12
L11:
	mov rax, 1
L12:
	test rax, rax
	jnz L0
L2:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_i: dq 0
