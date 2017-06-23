global  main
extern  printf
section .text
main:
	mov rax, 1
	push rax
	mov rax, v_p
	push rax
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rax, 2
	push rax
	mov rbx, v_p
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rax, v_p
	push rax
	xor rax, rax
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
	mov rbx, v_p
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	mov rsi, [rax]
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
