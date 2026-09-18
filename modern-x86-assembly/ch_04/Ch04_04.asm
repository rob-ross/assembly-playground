;------------------------------------------------------------------------------
; Ch04_04_fasm.s
;------------------------------------------------------------------------------

default rel

segment .text
;------------------------------------------------------------------------------
; size_t CountChars_a(const char* s, char c);
;------------------------------------------------------------------------------
global _CountChars_a
_CountChars_a:
; Perform required initializations


; Repeat loop until the entire string has been scanned


Done:
    mov rax,rcx                         ;rax = num_chars
    ret
