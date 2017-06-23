global  main
extern  printf
section .text
main:
	mov rax, 1
	cvtsi2sd xmm0, rax
	movq rax, xmm0
	push rax
	mov rbx, v_p
	mov rax, 32
	add rbx, rax
	mov rax, rbx
	add rax, 8
	pop rbx
	mov [rax], rbx
	mov rax, 2
	cvtsi2sd xmm0, rax
	movq rax, xmm0
	push rax
	mov rbx, v_p
	mov rax, 16
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rbx, v_p
	mov rax, 32
	add rbx, rax
	mov rax, rbx
	add rax, 8
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
	mov rbx, v_p
	mov rax, 16
	add rbx, rax
	mov rax, rbx
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
	v_p: times 80 db 0
	v_0: db " ", 0
