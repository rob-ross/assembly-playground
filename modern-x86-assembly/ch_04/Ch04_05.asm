;------------------------------------------------------------------------------
; Ch04_05.asm
;------------------------------------------------------------------------------

default rel

;------------------------------------------------------------------------------
; int64_t CompareArrays_a(const int32_t* x, const int32_t* y, int64_t n);
;
; Returns       -1          Value of n is invalid
;               0 <= i < n  Index of first non-matching element
;               n           All elements match
;------------------------------------------------------------------------------

section .text

global _CompareArrays_a
_CompareArrays_a:

; Validate n


; Compare the arrays for equality
; (rsi and rdi already contain pointers to arrays x and y)


; Calculate index of first non-match

Done:
    ret
