%include "colon.inc"
; The dictionary's filling
section .data
	
        colon 'one', one
        db 'Some dates', 0

        colon '+-=..!#&*', two
        db 'Vivaldi', 0

        db 'garbageddggdg'
        db 'mooooore', 0,0

        colon 'three-0.2', three
        db 'date', 0
	; root node
	colon 'last', last_node
	db 'Some bytes', 0
