global  main
extern  printf
section .text
main:
	mov rbx, [v_0]
	mov [v_a], rbx
	mov rax, [v_a]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	addsd xmm0, xmm1
	movq [v_b], xmm0
	movq xmm0, [v_a]
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
	movq xmm0, [v_b]
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
	mov rbx, [v_b]
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
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
