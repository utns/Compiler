global  main
extern  printf
section .text
main:
	push v_i
	mov rax, 1
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	jmp L0
L1:
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
L2:
	push v_i
	pop rax
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L0:
	mov rax, 5
	push rax
	pop rbx
	push v_i
	pop rax
	mov rax, [rax]
	cmp rax, rbx
	jle L4
	mov rax, 0
	jmp L5
L4:
	mov rax, 1
L5:
	push rax
	pop rax
	test rax, rax
	jnz L1
L3:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_i: dq 0
