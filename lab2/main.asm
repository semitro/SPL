%include "words.inc"
global _start

extern print_char
extern print_newline
extern exit
extern find_word
extern print_string
extern read_word
extern print_uint
extern print_string_err
extern string_length

section .bss
wantedWord:	
	resb 255
section .data
notFound:
	db 'key not found', 0
section .text
_start:
.test1:
	; read the key to find
	mov rdi, wantedWord
	mov rsi, 255
	call read_word
	
	mov rdi, wantedWord 
	mov rsi, last_node
	call find_word
	
	test rax, rax
	jz .notFound 
	mov r15, rax
	
	lea rdi, [rax + 8]
	call string_length


	
	add rax, r15
	mov rdi, rax
	lea rdi, [rdi + 9]
	call print_string
	call print_newline
	mov rdi, 0
	call exit
.notFound:
	
	mov rdi, notFound
	call print_string_err
	call print_newline
	mov rdi, 0
	call exit
