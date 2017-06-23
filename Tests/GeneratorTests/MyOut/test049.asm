global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rsi, [rbp + 32]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	movq xmm0, [rbp + 24]
	mov rax, 1
	mov rdi, formatFloat
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	mov rsi, [rbp + 16]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, 1
	push rax
	push qword [v_2]
	mov rax, 3
	push rax
	call foo0
	add rsp, 24
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " ", 0
	v_1: db " ", 0
	v_2: dq 2.300000
