global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	push rax
	push v_a
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [v_a]
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
	v_a: dq 0.000000
	v_0: dq 1.000000
