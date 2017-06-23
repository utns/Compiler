global  main
extern  printf
section .text
main:
	push qword [v_0]
	mov rbx, v_a
	mov rax, 32
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rbx, v_a
	mov rax, 32
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
	v_a: times 80 db 0
	v_0: dq 15.500000
