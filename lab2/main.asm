%include "colon.inc"

global _start

extern print_char
extern print_newline
extern exit
extern find_word
extern print_string
extern read_word
extern print_uint

section .data
	colon 'one', one
	db 'sfsf'
	colon 'two', two
	db 'chares'
	db 'garbageddggdg'
	db 'mooooore', 0,0
	colon 'three-0.2', three
	db 'date'

wantedWord:
	db 'three-0.2', 0
_start:
.test1:
	mov rdi, wantedWord
	mov rsi, 255
	call read_word
	
	mov rdi, wantedWord
	call print_string
	call print_newline

	mov rdi, wantedWord 
	mov rsi, three
	call find_word

	mov rdi, rax
	call print_uint
	;call print_string
	call print_newline
	call exit
