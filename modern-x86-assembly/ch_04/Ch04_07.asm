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
    xor     eax, eax        ; error return code
    test    edx, edx        ; is n <= 0?
    jle     BadArg

; Initialize registers for reversal operation
; (note: rsi and rdi already point to x[] and y[])
    mov     ecx, edx            ; rcx := n
    lea     rsi, [rsi+rcx*4-4]  ; rsi := &x[n-1], points to end of x[]

; Save caller's RFLAGS.DF, then set RFLAGS.DF to 1
    pushfq      ; save caller's RFLAGS.DF
    std         ; RFLAGS.DF := 1

; Repeat loop until array reversal is complete
Loop1:
    lodsd                   ; eax := *x--
    mov     [rdi], eax      ; *y := eax
    add     rdi, 4          ; y++
    sub     rcx, 1          ; n -= 1
    jnz     Loop1           ; jump if n != 0


; Restore caller's RFLAGS.DF and set return code
    popfq                   ; restore caller's RFLAGS.DF
    mov     eax, 1          ; set success return code

BadArg:
    ret
