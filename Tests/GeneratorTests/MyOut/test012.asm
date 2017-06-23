global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	divsd xmm0, [v_2]
	addsd xmm0, [v_3]
	subsd xmm0, [v_4]
	movq [v_a], xmm0
	movq xmm0, [v_a]
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
	v_0: dq 2.500000
	v_1: dq 4.000000
	v_2: dq 2.000000
	v_3: dq 45.000000
	v_4: dq 10.500000
