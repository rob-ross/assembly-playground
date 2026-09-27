;------------------------------------------------------------------------------
; Ch05_04.asm
;------------------------------------------------------------------------------
default rel


section .text

;------------------------------------------------------------------------------
;                                rdi           xmm0     xmm1
; void CompareF32_avx(uint8_t* cmp_results, float a, float b);
;------------------------------------------------------------------------------
global _CompareF32_avx
_CompareF32_avx:

; Set result flags based on compare status
    vucomiss    xmm0, xmm1      ; set RFLAGS.
    ; byte below is redundant as setcc always sets a byte
    setp        byte [rdi]      ; set first element of array to 1 if PF set (unordered)
    jnp         .L1              ; jump if PF not set
    ; otherwise zero out rest of array
    xor         rax, rax        ; set rax to 0
    mov         [rdi + 1], al   ;  zero out rest of array
    mov         [rdi + 2], al
    mov         [rdi + 3], al
    mov         [rdi + 4], al
    mov         [rdi + 5], al
    mov         [rdi + 6], al
    ret
.L1:
    setb        [rdi + 1]       ; set byte if a < b
    setbe       [rdi + 2]       ; set byte if a <= b
    sete        [rdi + 3]       ; set byte if a == b
    setne       [rdi + 4]       ; set byte if a != b
    seta        [rdi + 5]       ; set byte if a > b
    setae       [rdi + 6]       ; set byte if a >= b

    ret
