global  main
extern  printf
section .text
main:
	mov rax, 1
	push rax
	push v_p
	pop rax
	add rax, 0
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, 2
	push rax
	push v_p
	pop rax
	add rax, 8
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	push v_p
	pop rax
	add rax, 0
	push rax
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
	push v_p
	pop rax
	add rax, 8
	push rax
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_p: times 16 db 0
	v_0: db " ", 0
