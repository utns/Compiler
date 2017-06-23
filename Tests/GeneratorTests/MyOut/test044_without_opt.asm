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
	je L4
	mov rax, 0
	jmp L5
L4:
	mov rax, 1
L5:
	push rax
	pop rax
	test rax, rax
	jz L6
	jmp L2
	jmp L7
L6:
L7:
	push v_j
	mov rax, 1
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	jmp L8
L9:
	mov rax, [v_j]
	push rax
	mov rax, 5
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L12
	mov rax, 0
	jmp L13
L12:
	mov rax, 1
L13:
	push rax
	pop rax
	test rax, rax
	jz L14
	jmp L11
	jmp L15
L14:
L15:
	mov rax, [v_j]
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
	push rax
	mov rax, 0
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L16
	mov rax, 0
	jmp L17
L16:
	mov rax, 1
L17:
	push rax
	pop rax
	test rax, rax
	jz L18
	jmp L10
	jmp L19
L18:
L19:
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
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_j]
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
L10:
	push v_j
	pop rax
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L8:
	mov rax, 10
	push rax
	pop rbx
	push v_j
	pop rax
	mov rax, [rax]
	cmp rax, rbx
	jle L20
	mov rax, 0
	jmp L21
L20:
	mov rax, 1
L21:
	push rax
	pop rax
	test rax, rax
	jnz L9
L11:
	mov rax, [v_i]
	push rax
	mov rax, 6
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L22
	mov rax, 0
	jmp L23
L22:
	mov rax, 1
L23:
	push rax
	pop rax
	test rax, rax
	jz L24
	jmp L3
	jmp L25
L24:
L25:
L2:
	push v_i
	pop rax
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L0:
	mov rax, 10
	push rax
	pop rbx
	push v_i
	pop rax
	mov rax, [rax]
	cmp rax, rbx
	jle L26
	mov rax, 0
	jmp L27
L26:
	mov rax, 1
L27:
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
	v_j: dq 0
	v_0: db " ", 0
