global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, [v_0]
	push rax
	lea rax, [rbp + 16]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
foo10:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, [rbp + 16]
	push rax
	mov rax, [v_1]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	addsd xmm0, xmm1
	movq rax, xmm0
	push rax
	lea rax, [rbp + 24]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	sub rsp, 8
	sub rsp, 8
	call foo0
	add rsp, 0
	call foo10
	add rsp, 8
	pop rax
	movq xmm0, rax
	mov rax, 1
	mov rdi, formatFloat
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
	v_0: dq 3.500000
	v_1: dq 5.100000
