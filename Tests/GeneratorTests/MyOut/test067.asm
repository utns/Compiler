global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, [v_0]
	lea rax, [rbp + 16]
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
foo10:
	push rbp
	mov rbp, rsp
	mov rax, [rbp + 16]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	addsd xmm0, xmm1
	movq rbx, xmm0
	lea rax, [rbp + 24]
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	sub rsp, 8
	sub rsp, 8
	call foo0
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
