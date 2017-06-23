global  main
extern  printf
section .text
main:
	mov rax, 15
	push rax
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
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
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
