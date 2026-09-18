;------------------------------------------------------------------------------
; Ch04_07.asm
;------------------------------------------------------------------------------

default rel

section .text
;------------------------------------------------------------------------------
; int ReverseArrayI32_a(int32_t* y, const int32_t* x, int32_t n);
;------------------------------------------------------------------------------
global _ReverseArrayI32_a
_ReverseArrayI32_a:

; Make sure n is valid

; Initialize registers for reversal operation
; (note: rsi and rdi already point to x[] and y[])

; Save caller's RFLAGS.DF, then set RFLAGS.DF to 1

; Repeat loop until array reversal is complete

; Restore caller's RFLAGS.DF and set return code

BadArg:
    ret
