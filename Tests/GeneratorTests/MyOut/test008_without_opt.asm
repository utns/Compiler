global  main
extern  printf
section .text
main:
	mov rax, [v_0]
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
	mov rax, [v_2]
	push rax
	mov rax, [v_3]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	subsd xmm0, xmm1
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
	mov rax, [v_4]
	push rax
	mov rax, [v_5]
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
	mov rax, [v_6]
	push rax
	mov rax, [v_7]
	push rax
	pop rbx
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	divsd xmm0, xmm1
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
	v_0: dq 5.500000
	v_1: dq 2.750000
	v_2: dq 5.500000
	v_3: dq 2.750000
	v_4: dq 5.500000
	v_5: dq 2.750000
	v_6: dq 5.500000
	v_7: dq 2.750000
