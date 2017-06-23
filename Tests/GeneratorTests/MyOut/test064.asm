global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	push qword [v_0]
	mov rbx, [rbp + 16]
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rbx, [rbp + 16]
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	movq xmm0, [rax]
	mov rax, 1
	mov rdi, formatFloat
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	push qword [v_1]
	mov rbx, v_a
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push v_a
	call foo0
	add rsp, 8
	mov rbx, v_a
	mov rax, 8
	add rbx, rax
	mov rax, rbx
	movq xmm0, [rax]
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
	v_0: dq 15.200000
	v_a: times 24 db 0
	v_1: dq 155.100000
