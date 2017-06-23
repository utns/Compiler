global  main
extern  printf
section .text
main:
	push qword [v_0]
	push v_a
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push v_a
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	mov rax, [rax]
	mov rbx, [v_1]
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	movq rax, xmm0
	push rax
	mov rbx, v_a
	mov rax, 80
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push v_a
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	movq xmm0, [rax]
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
	mov rbx, v_a
	mov rax, 80
	add rbx, rax
	mov rax, rbx
	movq xmm0, [rax]
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
