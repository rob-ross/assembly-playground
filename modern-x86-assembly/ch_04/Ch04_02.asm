;------------------------------------------------------------------------------
; Ch04_02.asm
;------------------------------------------------------------------------------

default rel

section .text

;------------------------------------------------------------------------------
; void CalcArrayVals_a(int64_t* c, const int64_t* a, const int64_t* b, size_t n);
;------------------------------------------------------------------------------
global _CalcArrayVals_a
_CalcArrayVals_a:
; validate n
    or      rcx, rcx
    jz      Done        ; jump if n == 0

; initialize
    mov     r8, rdx     ; r8 := pointer to b[]
    mov     r11, -8     ; r11 := common offset for arrays

; calculate c[i] := a[i] * 25 / ( b[i] + 10);
Loop1:
    add     r11, 8          ; r11 := offset for a[i], b[i], and c[i]

    mov     rax, [rsi+r11]  ; rax := a[i]
    imul    rax, rax, 25    ; rax := a[i] * 25

    mov     r9, [r8+r11]   ; r9 := b[i]
    add     r9, 10         ; r9 := r9 + 10 == b[i] + 10

; convert quad word to octo word (double quad word)
    cqo                     ; rdx:rax := a[i] * 25, sign-extended into rdx
    idiv    r9              ; rax := (a[i] * 25) / (b[i] + 10)

    mov     [rdi+r11], rax  ; save quotient to c[i]

    sub     rcx, 1          ; n := n-1
    jnz     Loop1           ; repeat until n==0

Done:
    ret
