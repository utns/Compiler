global  main
extern  printf
section .text
main:
	mov rax, 50
	push rax
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	imul rbx
	push rax
	push v_a
	mov rax, 20
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
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
	push v_a
	mov rax, 20
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
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
	v_a: times 88 db 0
	v_0: db " ", 0
