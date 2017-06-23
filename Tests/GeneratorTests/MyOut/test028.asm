global  main
extern  printf
section .text
main:
	mov rbx, [v_0]
	lea rax, [v_p + 8]
	mov [rax], rbx
	mov rbx, [v_1]
	lea rax, [v_p + 16]
	mov [rax], rbx
	lea rax, [v_p + 8]
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
	lea rax, [v_p + 16]
	movq xmm0, [rax]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_p: times 32 db 0
	v_0: dq 1.500000
	v_1: dq 3.100000
	v_2: db " ", 0
