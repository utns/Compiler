global  main
extern  printf
section .text
main:
	mov rax, 3
	push rax
	push v_a
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push qword [v_0]
	push v_a
	xor rax, rax
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	cvtsi2sd xmm0, [rax]
	movq rbx, xmm0
	pop rax
	movq xmm0, rax
	movq xmm1, rbx
	mulsd xmm0, xmm1
	movq [v_f], xmm0
	movq xmm0, [v_f]
	mov rax, 1
	mov rdi, formatFloat
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_a: times 40 db 0
	v_f: dq 0.000000
	v_0: dq 10.500000
