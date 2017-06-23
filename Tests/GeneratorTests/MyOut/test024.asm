global  main
extern  printf
section .text
main:
	mov rbx, 1
	mov [v_p], rbx
	mov rbx, 2
	lea rax, [v_p + 8]
	mov [rax], rbx
	mov rax, v_p
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
	mov rsi, [v_p + 8]
	xor rax, rax
	mov rdi, formatInt
	sub rsp, 8
	call printf
	add rsp, 8
section .data
	formatInt: db "%ld", 0
	formatFloat: db "%f", 0
	formatNewLine: db 10, 0
	v_p: times 16 db 0
	v_0: db " ", 0
