global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, [v_0]
	push rax
	mov rax, [rbp + 16]
	push rax
	mov rax, 2
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
	mov rax, [rbp + 16]
	push rax
	mov rax, 2
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
	movq xmm0, rax
	mov rax, 1
	mov rdi, formatFloat
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, [v_1]
	push rax
	push v_a
	mov rax, 2
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
	push v_a
	call foo0
	add rsp, 8
	push v_a
	mov rax, 2
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
	v_0: dq 15.200000
	v_a: times 24 db 0
	v_1: dq 155.100000
