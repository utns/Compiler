global  main
extern  printf
section .text
main:
	mov rax, 1
	push rax
	pop rax
	cvtsi2sd xmm0, rax
	movq rax, xmm0
	push rax
	mov rax, [v_0]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	addsd xmm0, xmm1
	movq rax, xmm0
	push rax
	pop rax
	movq xmm0, rax
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: dq 1.500000
