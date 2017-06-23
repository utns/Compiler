global  main
extern  printf
section .text
main:
	push qword [v_0]
	push v_points
	xor rax, rax
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push qword [v_1]
	mov rbx, v_points
	mov rax, 144
	add rbx, rax
	mov rax, rbx
	add rax, 8
	pop rbx
	mov [rax], rbx
	push v_points
	xor rax, rax
	mov rbx, 16
	imul rbx
	pop rbx
	add rbx, rax
	mov rax, rbx
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
	mov rbx, v_points
	mov rax, 144
	add rbx, rax
	mov rax, rbx
	add rax, 8
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
	v_points: times 160 db 0
	v_0: dq 33.500000
	v_1: dq 0.100000
	v_2: db " ", 0
