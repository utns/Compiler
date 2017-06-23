global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, [v_0]
	lea rax, [rbp + 16]
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	sub rsp, 8
	call foo0
	mov rax, v_a
	pop rbx
	mov [rax], rbx
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
	v_0: dq 3.500000
	v_a: dq 0.000000
