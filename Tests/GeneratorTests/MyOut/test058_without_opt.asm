global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, [rbp + 16]
	push rax
	lea rax, [rbp - 8]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [rbp - 8]
	push rax
	pop rax
	mov rsi, rax
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
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, 5
	push rax
	call foo0
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
