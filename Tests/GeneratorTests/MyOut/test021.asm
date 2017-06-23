global  main
extern  printf
section .text
main:
	mov rax, 1
	cvtsi2sd xmm0, rax
	addsd xmm0, [v_0]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: dq 1.500000
