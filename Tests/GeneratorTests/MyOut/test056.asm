global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rax, 3
	push rax
	lea rax, [rbp + 1608]
	mov rbx, rax
	mov rax, 784
	sub rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	mov rax, 4
	push rax
	lea rax, [rbp + 808]
	mov rbx, rax
	mov rax, 784
	sub rbx, rax
	mov rax, rbx
	pop rbx
	mov [rax], rbx
	lea rax, [rbp + 1608]
	mov rbx, rax
	mov rax, 784
	sub rbx, rax
	mov rax, rbx
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	lea rax, [rbp + 808]
	mov rbx, rax
	mov rax, 784
	sub rbx, rax
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
	mov rax, v_p
	mov rbx, 1600
	xor rcx, rcx
L0:
	cmp rcx, rbx
	jge L1
	push qword [rax]
	add rax, 8
	add rcx, 8
	jmp L0
L1:
	call foo0
	add rsp, 1600
	mov rbx, v_p
	mov rax, 784
	add rbx, rax
	mov rax, rbx
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	lea rax, [v_p + 800]
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
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db " ", 0
	v_p: times 1600 db 0
	v_1: db " ", 0
