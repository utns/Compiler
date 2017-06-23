global  main
extern  printf
section .text
main:
	mov rax, 2
	push rax
	push v_a
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_a]
	push rax
	mov rax, 10
	push rax
	pop rbx
	pop rax
	add rax, rbx
	push rax
	push v_b
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, 0
	push rax
	push v_c
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_a]
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
	mov rax, [v_b]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_a]
	push rax
	mov rax, [v_b]
	push rax
	pop rbx
	pop rax
	imul rbx
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_b]
	push rax
	mov rax, [v_c]
	push rax
	pop rbx
	pop rax
	imul rbx
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_a: dq 0
	v_b: dq 0
	v_c: dq 0
	v_0: db " ", 0
	v_1: db " ", 0
	v_2: db " ", 0
