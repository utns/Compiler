global  main
extern  printf
section .text
f0:
	push rbp
	mov rbp, rsp
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
g0:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov rbx, 3
	lea rax, [rbp - 8]
	mov [rax], rbx
	mov rbx, 2
	lea rax, [rbp - 16]
	mov [rax], rbx
	lea rax, [rbp - 8]
	push rax
	call f0
	add rsp, 8
	mov rsi, [rbp - 8]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	mov rsi, [rbp - 16]
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
	call f0
	add rsp, 8
	call g0
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " ", 0
	v_1: db " ", 0
	v_p: times 16 db 0
