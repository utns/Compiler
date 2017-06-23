global  main
extern  printf
section .text
main:
	mov rax, 1
	cvtsi2sd xmm0, rax
	movq [v_a], xmm0
	movq xmm0, [v_a]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_a: dq 0.000000
