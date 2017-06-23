global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	push v_a
	mov rax, 2
	push rax
	pop rax
	sub rax, 1
	mov rbx, 80
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	mov rax, 15
	push rax
	pop rax
	sub rax, 11
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	push v_a
	mov rax, 2
	push rax
	pop rax
	sub rax, 1
	mov rbx, 80
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	mov rax, 15
	push rax
	pop rax
	sub rax, 11
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
	v_a: times 400 db 0
	v_0: dq 111.110000
