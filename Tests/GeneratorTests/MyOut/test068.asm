global  main
extern  printf
section .text
foo0:
	push rbp
	mov rbp, rsp
	mov rax, [rbp + 24]
	mov rbx, 3
	add rax, rbx
	mov rbx, rax
	lea rax, [rbp + 40]
	mov [rax], rbx
	mov rax, [rbp + 16]
	mov rbx, 5
	sub rax, rbx
	mov rbx, rax
	lea rax, [rbp + 32]
	mov [rax], rbx
	mov rsp, rbp
	pop rbp
	ret
main:
	mov rbx, 3
	mov [v_p1], rbx
	mov rbx, 4
	lea rax, [v_p1 + 8]
	mov [rax], rbx
	sub rsp, 16
	mov rax, v_p1
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
	mov rax, v_p2
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
	mov rax, v_p1
	mov rsi, [rax]
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
	mov rsi, [v_p1 + 8]
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
	mov rax, v_p2
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
	mov rsi, [v_p2 + 8]
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
