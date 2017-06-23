global  main
extern  printf
section .text
main:
	mov rax, [v_0]
	mov rbx, 9223372036854775808
	xor rax, rbx
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
	mov rax, [v_1]
	mov rbx, 9223372036854775808
	xor rax, rbx
	mov rbx, 9223372036854775808
	xor rax, rbx
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
	mov rbx, 9223372036854775808
	xor rax, rbx
	mov rbx, 9223372036854775808
	xor rax, rbx
	mov rbx, 9223372036854775808
	xor rax, rbx
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
	v_0: dq 1.100000
	v_1: dq 1.100000
	v_2: dq 1.100000
