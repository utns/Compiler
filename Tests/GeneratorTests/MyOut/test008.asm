global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	addsd xmm0, xmm1
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
	mov rax, [v_2]
	mov rbx, [v_3]
	movq xmm0, rax
	movq xmm1, rbx
	subsd xmm0, xmm1
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
	mov rax, [v_4]
	mov rbx, [v_5]
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
	mov rax, [v_6]
	mov rbx, [v_7]
	movq xmm0, rax
	movq xmm1, rbx
	divsd xmm0, xmm1
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
	v_0: dq 5.500000
	v_1: dq 2.750000
	v_2: dq 5.500000
	v_3: dq 2.750000
	v_4: dq 5.500000
	v_5: dq 2.750000
	v_6: dq 5.500000
	v_7: dq 2.750000
