global  main
extern  printf
section .text
main:
	mov rax, 220
	push rax
	mov rax, 60
	mov rbx, 3
	xor rdx, rdx
	idiv rbx
	mov rbx, rax
	pop rax
	sub rax, rbx
	mov rbx, 150
	add rax, rbx
	mov [v_a], rax
	mov rsi, [v_a]
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
	v_a: dq 0
