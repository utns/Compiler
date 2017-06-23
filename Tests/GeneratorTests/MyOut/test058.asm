global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rbx, [rbp + 16]
	lea rax, [rbp - 8]
	mov [rax], rbx
	mov rsi, [rbp - 8]
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, formatNewLine
	sub rsp, 8
	call printf
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
