global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 24
	mov rax, [rbp + 16]
	push rax
	lea rax, [rbp - 8]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [rbp + 16]
	push rax
	pop rax
	cvtsi2sd xmm0, rax
	movq rax, xmm0
	push rax
	lea rax, [rbp - 16]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [rbp - 8]
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	imul rbx
	push rax
	lea rax, [rbp - 24]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [rbp - 8]
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
	mov rax, [rbp - 16]
	push rax
	pop rax
	movq xmm0, rax
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
	mov rax, [rbp - 24]
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
