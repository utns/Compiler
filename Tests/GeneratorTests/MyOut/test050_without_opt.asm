global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, [rbp + 16]
	push rax
	mov rax, 1
	push rax
	pop rbx
	pop rax
	add rax, rbx
	push rax
	call foo1
	add rsp, 8
	mov rax, [rbp + 16]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
foo1:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, [rbp + 16]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, 3
	push rax
	call foo0
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " - 1", 0
	v_1: db " - 2", 0
