global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	mov rax, [v_1]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	movq rax, xmm0
	push rax
	push v_a
	mov rax, 20
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	push v_a
	mov rax, 10
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	movq xmm0, rax
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	push v_a
	mov rax, 20
	push rax
	pop rax
	sub rax, 10
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
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
	v_a: times 88 db 0
	v_0: dq 50.000000
	v_1: dq 2.000000
	v_2: db " ", 0
