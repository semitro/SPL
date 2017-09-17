extern string_equals
; This file contains the find_word function
; Args:
; 1, rdi) A pointer to a null terminated key string
; 2, rsi) A pointer to the last word in the dicntionary
; (the word in which the next reference is null. This word is added last)
global find_word

find_word:
	push rdi	    ; string_equals spoils these registers  
	push rsi	    ;   
	lea  rsi, [rsi + 8] ; We now that the key locates after 8 bytes
        	            ; List structure:
                	    ; 1) Pointer to the next node (64 bit)
                  	    ; 2) Key-\0 string
                    	    ; 3) Date-\0 string

	call string_equals
	pop rsi
	pop rdi

	test rax, rax	    ; 1 if equals, 0 otherwise.
	jnz  .found
	mov  rsi, [rsi]	    ; Now rsi is the pointer to the next node
	test rsi, rsi	    ; If the reference is null, we've gone over
			    ; All the nodes
	jnz find_word	    ; Repeat if there is the next node
	xor eax, eax	    ; Return 0 if the word have not been found
	ret
.found:
	mov rax, rsi  	    ; If success, return the record's addr
	ret

