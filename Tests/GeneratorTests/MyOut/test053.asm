global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, [v_0]
	mov rax, [rbp + 16]
	mov [rax], rbx
	mov rax, [rbp + 16]
	movq xmm0, [rax]
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
	mov rbx, [v_1]
	mov [v_a], rbx
	push v_a
	call foo0
	add rsp, 8
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
	v_0: dq 5.200000
	v_a: dq 0.000000
	v_1: dq 4.100000
