global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 800
	push qword [rbp + 16]
	lea rax, [rbp - 8]
	mov rbx, rax
	mov rax, 112
	sub rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	lea rax, [rbp - 8]
	mov rbx, rax
	mov rax, 112
	sub rbx, rax
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
	push qword [v_0]
	call foo0
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: dq 5.300000
