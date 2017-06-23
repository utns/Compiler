global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, 3
	push rax
	lea rax, [rbp + 16]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	sub rsp, 8
	call foo0
	add rsp, 0
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
