global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rax, 3
	push rax
	mov rbx, [rbp + 16]
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rax, 4
	push rax
	mov rax, [rbp + 16]
	add rax, 800
	mov rbx, rax
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rbx, [rbp + 16]
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	mov rax, [rbp + 16]
	add rax, 800
	mov rbx, rax
	mov rax, 784
	add rbx, rax
	mov rax, rbx
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
	mov rax, 1
	push rax
	mov rbx, v_p
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rax, 2
	push rax
	lea rax, [v_p + 800]
	mov rbx, rax
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	push v_p
	call foo0
	add rsp, 8
	mov rbx, v_p
	mov rax, 784
	add rbx, rax
	mov rax, rbx
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
	lea rax, [v_p + 800]
	mov rbx, rax
	mov rax, 784
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
	v_0: db " ", 0
	v_p: times 1600 db 0
	v_1: db " ", 0
