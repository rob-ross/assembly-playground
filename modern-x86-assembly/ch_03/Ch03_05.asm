;------------------------------------------------------------------------------
; Ch03_05_fasm.s
;------------------------------------------------------------------------------

default rel

section .text

extern _g_ValMax
;------------------------------------------------------------------------------
; bool CalcSumCubes_a(int64_t* sum, int64_t n);
;------------------------------------------------------------------------------
global _CalcSumCubes_a
_CalcSumCubes_a:
; validate  0 < n <= g_ValMax
    test    rsi, rsi        ; sets the SF, ZF, and PF status flags
    jle     BadArg          ; jump if n <=0
    cmp     rsi, [_g_ValMax]
    jg      BadArg          ; jump if n > g_ValMax

; Initialize
    xor     r10, r10        ; i := 0
    xor     eax, eax        ; sum := 0

Loop1:
    add     r10, 1          ; i := i + 1
    mov     r11, r10        ; r11 := i
    imul    r11, r11        ; r11 : = i * i
    imul    r11, r10        ; r11 : = i * i * i
    add     rax, r11        ; sum := sum + i^3

    cmp    r10, rsi
    jl     Loop1           ; jump if i < n

Done:
    mov     [rdi], rax  ; copy sum to argument pointer location
    mov     eax, 1      ; rc := true
    ret

BadArg:
    mov     qword [rdi], 0  ; sum := 0 (error)
    xor     eax, eax        ; rc := false
    ret
