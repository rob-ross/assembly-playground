;------------------------------------------------------------------------------
; Ch08_01.asm
; Created by Rob Ross on 9/29/26.
;
;------------------------------------------------------------------------------

default rel


section .text

;------------------------------------------------------------------------------
;                        rdi         rsi              rdx             rcx
; void AddI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

global _AddI16_avx
_AddI16_avx:

    vmovdqa     xmm0,   [rdx]   ; xmm0 = a (pointer to int16_t[8])
    vmovdqa     xmm1,   [rcx]   ; xmm1 = b (pointer to int16_t[8])

    ; xmm2[0..7] = a[0..7] + b[0..7]
    vpaddw      xmm2,   xmm0, xmm1  ; packed add - wrap-around
    vpaddsw     xmm3,   xmm0, xmm1  ; packed add - saturated

    ; save sums to output arg pointer
    vmovdqa     [rdi],  xmm2        ; c1 copies xmm2[127:0] to [rdi]
    vmovdqa     [rsi],  xmm3        ; save c2

    ret


;------------------------------------------------------------------------------
;                        rdi         rsi               rdx             rcx
; void SubI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

global _SubI16_avx
_SubI16_avx:
    vmovdqa     xmm0,   [rdx]   ; xmm0 = a (pointer to int16_t[8])
    vmovdqa     xmm1,   [rcx]   ; xmm1 = b (pointer to int16_t[8])

    vpsubw      xmm2,   xmm0, xmm1  ; packed sub - wrap-around
    vpsubsw     xmm3,   xmm0, xmm1  ; packed sub - saturated

    vmovdqa     [rdi],  xmm2        ; save c1
    vmovdqa     [rsi],  xmm3        ; save c2

    ret
