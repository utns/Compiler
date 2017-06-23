global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	sub rsp, 0
	lea rax, [rbp + 24]
	push rax
	pop rax
	sub rax, 0
	push rax
	pop rax
	mov rax, [rax]
	push rax
	mov rax, 3
	push rax
	pop rbx
	pop rax
	add rax, rbx
	push rax
	lea rax, [rbp + 40]
	push rax
	pop rax
	sub rax, 0
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	lea rax, [rbp + 24]
	push rax
	pop rax
	sub rax, 8
	push rax
	pop rax
	mov rax, [rax]
	push rax
	mov rax, 5
	push rax
	pop rbx
	pop rax
	sub rax, rbx
	push rax
	lea rax, [rbp + 40]
	push rax
	pop rax
	sub rax, 8
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rax, 3
	push rax
	push v_p1
	pop rax
	add rax, 0
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	mov rax, 4
	push rax
	push v_p1
	pop rax
	add rax, 8
	push rax
	pop rax
	pop rbx
	mov [rax], rbx
	sub rsp, 16
	mov rax, v_p1
	mov rbx, 16
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
	add rsp, 16
	push v_p2
	pop rax
	mov rbx, 16
	lea rax, [rax + 8]
L2:
	cmp rbx, 0
	jle L3
	pop rdx
	mov [rax], rdx
	sub rax, 8
	sub rbx, 8
	jmp L2
L3:
	push v_p1
	pop rax
	add rax, 0
	push rax
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	mov rsi, rax
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
	push v_p1
	pop rax
	add rax, 8
	push rax
	pop rax
	mov rax, [rax]
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
	push v_p2
	pop rax
	add rax, 0
	push rax
	pop rax
	mov rax, [rax]
	push rax
	pop rax
	mov rsi, rax
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
	push v_p2
	pop rax
	add rax, 8
	push rax
	pop rax
	mov rax, [rax]
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
	v_p1: times 16 db 0
	v_p2: times 16 db 0
	v_0: db " ", 0
	v_1: db " ", 0
