global  main
extern  printf
section .text
main:
	mov rax, 1
	cvtsi2sd xmm0, rax
	movq [v_p], xmm0
	mov rax, 2
	cvtsi2sd xmm0, rax
	movq rbx, xmm0
	lea rax, [v_p + 8]
	mov [rax], rbx
	mov rax, v_p
	movq xmm0, [rax]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	lea rax, [v_p + 8]
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
	v_p: times 16 db 0
	v_0: db " ", 0
