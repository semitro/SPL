; this macro accepts two args:
; 1) A key string. (you do not need to write \0 symbol)
; 2) A current element label

%macro colon 2

%ifndef prev	; Automatically refering to the previous element.
 %define prev 0
%endif

%2:	     ; The label
dq   prev    ; A pointer to the next element
db %1, 0     ; Key string
%define prev %2
%endmacro

