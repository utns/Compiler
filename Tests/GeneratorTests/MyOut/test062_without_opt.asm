global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, [rbp + 16]
	push rax
	mov rax, 2
	push rax
	pop rbx
	pop rax
	imul rbx
	push rax
	lea rax, [rbp - 8]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	lea rax, [rbp - 8]
	push rax
	call foo1
	add rsp, 8
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
foo1:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, [rbp + 16]
	mov rax, [rax]
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	add rax, rbx
	push rax
	lea rax, [rbp - 8]
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, [rbp - 8]
	push rax
	mov rax, [rbp + 16]
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
	call printf
	xor rax, rax
	mov rdi, formatNewLine
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
