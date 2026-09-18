;------------------------------------------------------------------------------
; Ch04_01.asm
;------------------------------------------------------------------------------
default rel

segment .text

;------------------------------------------------------------------------------
; int64_t SumElementsI32_a(const int32_t* x, size_t n);
;   returns the sum of the n int32_t elements in the array pointed by x
;------------------------------------------------------------------------------
global _SumElementsI32_a
_SumElementsI32_a:

; initialize
    xor     eax, eax    ; (eax) sum := 0
    sub     rdi, 4      ; rdi := &x[-1]

; validate n
    or      rsi, rsi    ; sets condition flags
    jz      Done        ; jump if n == 0

; Sum the elements of the array
Loop1:
    add     rdi, 4      ; rdi points to next element in x[]

    movsxd  r11, [rdi]  ; load (sign-extended) element from x[]
    add     rax, r11    ; update sum

    sub     rsi, 1      ; n := n - 1
    jnz     Loop1       ; repeat until n is zero

Done:
    ret
