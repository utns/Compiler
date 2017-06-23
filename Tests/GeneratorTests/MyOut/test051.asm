global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, 5
	mov rax, [rbp + 16]
	mov [rax], rbx
	mov rax, [rbp + 16]
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rbx, 4
	mov [v_a], rbx
	push v_a
	call foo0
	add rsp, 8
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
