global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 800
	mov rax, [rbp + 16]
	push rax
	lea rax, [rbp - 8]
	push rax
	mov rax, 15
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	lea rax, [rbp - 8]
	push rax
	mov rax, 15
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
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
	mov rax, [v_0]
	push rax
	call foo0
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: dq 5.300000
