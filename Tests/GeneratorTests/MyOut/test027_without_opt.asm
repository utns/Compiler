global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	push v_points
	mov rax, 1
	push rax
	pop rax
	sub rax, 1
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	add rax, 0
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_1]
	push rax
	push v_points
	mov rax, 10
	push rax
	pop rax
	sub rax, 1
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	add rax, 8
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	push v_points
	mov rax, 1
	push rax
	pop rax
	sub rax, 1
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	add rax, 0
	push rax
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
	push v_points
	mov rax, 10
	push rax
	pop rax
	sub rax, 1
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	add rax, 8
	push rax
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_points: times 160 db 0
	v_0: dq 33.500000
	v_1: dq 0.100000
	v_2: db " ", 0
