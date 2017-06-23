global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 24
	mov rbx, [rbp + 16]
	lea rax, [rbp - 8]
	mov [rax], rbx
	cvtsi2sd xmm0, [rbp + 16]
	movq rbx, xmm0
	lea rax, [rbp - 16]
	mov [rax], rbx
	mov rax, [rbp - 8]
	mov rbx, 2
	imul rbx
	mov rbx, rax
	lea rax, [rbp - 24]
	mov [rax], rbx
	mov rsi, [rbp - 8]
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
	movq xmm0, [rbp - 16]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
	mov rsi, [rbp - 24]
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, 5
	push rax
	call foo0
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " ", 0
	v_1: db " ", 0
