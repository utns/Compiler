global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, 3
	mov rax, [rbp + 16]
	mov [rax], rbx
	mov rax, 4
	push rax
	mov rax, [rbp + 16]
	add rax, 8
	pop rbx
	mov [rax], rbx
	mov rax, [rbp + 16]
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	mov rax, [rbp + 16]
	add rax, 8
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
	mov rbx, 1
	mov [v_p], rbx
	mov rbx, 2
	lea rax, [v_p + 8]
	mov [rax], rbx
	push v_p
	call foo0
	add rsp, 8
	mov rax, v_p
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
	mov rsi, [v_p + 8]
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
	v_0: db " ", 0
	v_p: times 16 db 0
	v_1: db " ", 0
