global  main
extern  printf
section .text
main:
	mov rax, 0
	push rax
	push v_i
	pop rax
	pop rbx
	mov [rax], rbx
	jmp L1
L0:
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
	mov rax, [v_i]
	push rax
	mov rax, 9
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L3
	mov rax, 0
	jmp L4
L3:
	mov rax, 1
L4:
	push rax
	pop rax
	test rax, rax
	jz L5
	jmp L2
	jmp L6
L5:
L6:
	mov rax, [v_i]
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L7
	mov rax, 0
	jmp L8
L7:
	mov rax, 1
L8:
	push rax
	pop rax
	test rax, rax
	jz L9
	jmp L1
	jmp L10
L9:
L10:
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
L1:
	mov rax, [v_i]
	push rax
	mov rax, 10
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L11
	mov rax, 0
	jmp L12
L11:
	mov rax, 1
L12:
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
