global  main
extern  printf
section .text
main:
	mov rax, v_i
	mov rbx, 1
	mov [rax], rbx
	jmp L0
L1:
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
L2:
	mov rax, v_i
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L0:
	mov rbx, 5
	mov rax, [v_i]
	cmp rax, rbx
	jle L4
	xor rax, rax
	jmp L5
L4:
	mov rax, 1
L5:
	test rax, rax
	jnz L1
L3:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_i: dq 0
