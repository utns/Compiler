global  main
extern  printf
section .text
main:
	xor rax, rax
	test rax, rax
	jz L0
	xor rax, rax
	mov rdi, v_0
	sub rsp, 8
	call printf
	add rsp, 8
	jmp L1
L0:
	xor rax, rax
	mov rdi, v_1
	sub rsp, 8
	call printf
	add rsp, 8
L1:
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_0: db "then", 0
	v_1: db "else", 0
