global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	mov rax, 3
	push rax
	lea rax, [rbp + 1608]
	push rax
	pop rax
	sub rax, 0
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, 4
	push rax
	lea rax, [rbp + 1608]
	push rax
	pop rax
	sub rax, 800
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	lea rax, [rbp + 1608]
	push rax
	pop rax
	sub rax, 0
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	lea rax, [rbp + 1608]
	push rax
	pop rax
	sub rax, 800
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	sub rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
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
	mov rax, 1
	push rax
	push v_p
	pop rax
	add rax, 0
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, 2
	push rax
	push v_p
	pop rax
	add rax, 800
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, v_p
	mov rbx, 1600
	xor rcx, rcx
L0:
	cmp rcx, rbx
	jge L1
	mov rdx, [rax]
	push rdx
	add rax, 8
	add rcx, 8
	jmp L0
L1:
	call foo0
	add rsp, 1600
	push v_p
	pop rax
	add rax, 0
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	push v_p
	pop rax
	add rax, 800
	push rax
	mov rax, 99
	push rax
	pop rax
	sub rax, 1
	mov rbx, 8
	imul rbx
	pop rbx
	add rbx, rax
	push rbx
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	mov rsi, rax
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, formatNewLine
	call printf
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " ", 0
	v_p: times 1600 db 0
	v_1: db " ", 0
