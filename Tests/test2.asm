global  main
extern  printf
section .text
main:
	mov rbx, 1
	mov [rax], rbx
	jmp L0
L1:
	mov rbx, 11
	mov [rax], rbx
	jmp L4
L5:
	imul qword [v_j]
	push rax
	push v_a
	mov rax, [v_i]
	mov rbx, 1
	sub rax, rbx
	mov rbx, 80
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	mov rax, [v_j]
	mov rbx, 11
	sub rax, rbx
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
L6:
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L4:
	mov rax, [v_j]
	cmp rax, rbx
	jle L8
	xor rax, rax
	jmp L9
L8:
L9:
	jnz L5
L7:
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L0:
	mov rax, [v_i]
	cmp rax, rbx
	jle L10
	xor rax, rax
	jmp L11
L10:
L11:
	jnz L1
L3:
	mov rbx, 1
	mov [rax], rbx
	jmp L12
L13:
	mov rbx, 11
	mov [rax], rbx
	jmp L16
L17:
	mov rax, [v_i]
	mov rbx, 1
	sub rax, rbx
	mov rbx, 80
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	mov rax, [v_j]
	mov rbx, 11
	sub rax, rbx
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	mov rsi, [rax]
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
L18:
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L16:
	mov rax, [v_j]
	cmp rax, rbx
	jle L20
	xor rax, rax
	jmp L21
L20:
L21:
	jnz L17
L19:
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	add rsp, 8
L14:
	mov rbx, [rax]
	add rbx, 1
	mov [rax], rbx
L12:
	mov rax, [v_i]
	cmp rax, rbx
	jle L22
	xor rax, rax
	jmp L23
L22:
L23:
	jnz L13
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_a: times 400 db 0
	v_i: dq 0
	v_j: dq 0
	v_0: db " ", 0
