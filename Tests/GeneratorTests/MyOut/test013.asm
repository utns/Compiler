global  main
extern  printf
section .text
main:
	mov rbx, 2
	mov [v_a], rbx
	mov rax, [v_a]
	mov rbx, 10
	add rax, rbx
	mov [v_b], rax
	xor rax, rax
	mov [v_c], rax
	mov rsi, [v_a]
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	mov rsi, [v_b]
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
	mov rax, [v_a]
	imul qword [v_b]
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
	xor rax, rax
	mov rdi, v_2
	sub rsp, 8
	call printf
	add rsp, 8
	mov rax, [v_b]
	imul qword [v_c]
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
	v_a: dq 0
	v_b: dq 0
	v_c: dq 0
	v_0: db " ", 0
	v_1: db " ", 0
	v_2: db " ", 0
