global  main
extern  printf
section .text
main:
	mov rax, 2
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	add rax, rbx
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
	mov rax, 2
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	sub rax, rbx
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
	mov rax, 20
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	imul rbx
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
	mov rax, 20
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv rbx
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
	mov rax, 20
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv rbx
	mov rax, rdx
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
