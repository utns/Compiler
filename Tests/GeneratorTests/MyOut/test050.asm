global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rax, [rbp + 16]
	mov rbx, 1
	add rax, rbx
	push rax
	call foo1
	add rsp, 8
	mov rsi, [rbp + 16]
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
	mov rsi, [rbp + 16]
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
