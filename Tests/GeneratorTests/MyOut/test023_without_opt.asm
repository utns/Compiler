global  main
extern  printf
section .text
main:
	mov rax, 3
	push rax
	push v_a
	mov rax, 1
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_0]
	push rax
	push v_a
	mov rax, 1
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	cvtsi2sd xmm0, rax
	movq rax, xmm0
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	movq rax, xmm0
	push rax
	push v_f
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_f]
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
	v_a: times 40 db 0
	v_f: dq 0.000000
	v_0: dq 10.500000
