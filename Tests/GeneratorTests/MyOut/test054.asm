global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rbx, 3
	lea rax, [rbp + 24]
	mov [rax], rbx
	mov rbx, 4
	lea rax, [rbp + 16]
	mov [rax], rbx
	mov rsi, [rbp + 24]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_0
	call printf
	mov rsi, [rbp + 16]
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
	mov rax, v_p
	mov rbx, 16
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
	add rsp, 16
	mov rax, v_p
	mov rsi, [rax]
	xor rax, rax
	mov rdi, formatInt
	call printf
	xor rax, rax
	mov rdi, v_1
	call printf
	mov rsi, [v_p + 8]
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
	v_p: times 16 db 0
	v_1: db " ", 0
