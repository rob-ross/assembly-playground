;------------------------------------------------------------------------------
; Ch08_03.asm
; Created by Rob Ross on 10/13/26.
;
;------------------------------------------------------------------------------

default rel

section .text

;------------------------------------------------------------------------------
;                       rdi,             rsi,             rdx
; void AndU16_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------
global _AndU16_avx
_AndU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 := a
    vpand       xmm1, xmm0, [rdx]   ; xmm1 := a & b
    vmovdqa     [rdi], xmm1         ; save result
    ret



;------------------------------------------------------------------------------
; void OrU16_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------
global _OrU16_avx
_OrU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 := a
    vpor        xmm1, xmm0, [rdx]   ; xmm1 := a | b
    vmovdqa     [rdi], xmm1         ; save result
    ret



;------------------------------------------------------------------------------
; void XorU16_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------
global _XorU16_avx
_XorU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 := a
    vpxor       xmm1, xmm0, [rdx]   ; xmm1 := a ^ b
    vmovdqa     [rdi], xmm1         ; save result
    ret
