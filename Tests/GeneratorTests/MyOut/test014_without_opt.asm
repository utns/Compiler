global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	push v_a
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_a]
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
	push v_b
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_a]
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
	mov rax, [v_b]
	push rax
	pop rax
	movq xmm0, rax
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_3
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_a]
	push rax
	mov rax, [v_b]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	movq rax, xmm0
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
	v_a: dq 0.000000
	v_b: dq 0.000000
	v_0: dq 2.000000
	v_1: dq 10.000000
	v_2: db " ", 0
	v_3: db " ", 0
