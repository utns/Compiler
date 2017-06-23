global  main
extern  printf
section .text
main:
	mov rax, v_i
	mov rbx, 1
	mov [rax], rbx
	jmp L0
L1:
	mov rax, [v_i]
	mov rbx, 2
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
	mov rbx, 1
	cmp rax, rbx
	je L4
	xor rax, rax
	jmp L5
L4:
	mov rax, 1
L5:
	test rax, rax
	jz L6
	jmp L2
	jmp L7
L6:
L7:
	mov rax, v_j
	mov rbx, 1
	mov [rax], rbx
	jmp L8
L9:
	mov rax, [v_j]
	mov rbx, 5
	cmp rax, rbx
	je L12
	xor rax, rax
	jmp L13
L12:
	mov rax, 1
L13:
	test rax, rax
	jz L14
	jmp L11
	jmp L15
L14:
L15:
	mov rax, [v_j]
	mov rbx, 2
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
	push rax
	xor rax, rax
	mov rbx, rax
	pop rax
	cmp rax, rbx
	je L16
	xor rax, rax
	jmp L17
L16:
	mov rax, 1
L17:
	test rax, rax
	jz L18
	jmp L10
	jmp L19
L18:
L19:
	mov rsi, [v_i]
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
	mov rsi, [v_j]
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
	mov rax, v_j
	add rbx, qword [rax]
	mov [rax], rbx
L8:
	mov rbx, 10
	mov rax, v_j
	mov rax, [rax]
	cmp rax, rbx
	jle L20
	xor rax, rax
	jmp L21
L20:
	mov rax, 1
L21:
	test rax, rax
	jnz L9
L11:
	mov rax, [v_i]
	mov rbx, 6
	cmp rax, rbx
	je L22
	xor rax, rax
	jmp L23
L22:
	mov rax, 1
L23:
	test rax, rax
	jz L24
	jmp L3
	jmp L25
L24:
L25:
L2:
	mov rax, v_i
	add rbx, qword [rax]
	mov [rax], rbx
L0:
	mov rbx, 10
	mov rax, v_i
	mov rax, [rax]
	cmp rax, rbx
	jle L26
	xor rax, rax
	jmp L27
L26:
	mov rax, 1
L27:
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
