;------------------------------------------------------------------------------
; Ch08_02.asm
; Created by Rob Ross on 9/29/26.
;
;------------------------------------------------------------------------------

default rel


section .text

;------------------------------------------------------------------------------
;                         rdi              rsi              rdx
; void MulI16_avx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

global _MulI16_avx
_MulI16_avx:

    vmovdqa     xmm0, [rsi]     ; copy 16 aligned bytes from *a
    vmovdqa     xmm1, [rdx]     ; copy 16 aligned bytes from *b

    ; Packed Multiply Low Signed Word
    vpmullw     xmm2, xmm0, xmm1 ; packed multiply low signed word
    ; Packed Multiply High Signed Word
    vpmulhw     xmm3, xmm0, xmm1 ; packed mul high signed word

    ; Unpack and Interleave Low Words
    vpunpcklwd  xmm4, xmm2, xmm3    ; packed low-order dwords
    ; Unpack and Interleave High Words
    vpunpckhwd  xmm5, xmm2, xmm3    ; packed high-order dwords

    vmovdqa     [rdi],    xmm4         ; save c[0]
    vmovdqa     [rdi+16], xmm5         ; save c[1]

    ret

;------------------------------------------------------------------------------
;                        rdi              rsi             rdx
; void MulI32a_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

global _MulI32a_avx
_MulI32a_avx:

    ; Move Aligned Double Quadword
    vmovdqa     xmm0, [rsi]     ; xmm0 = a
    vmovdqa     xmm1, [rdx]     ; xmm1 = b

    ; Packed Multiply and Store Low Signed Doubleword
    vpmulld     xmm2, xmm0, xmm1    ; xmm2 = a * p, packed mul - low result

    vmovdqa     [rdi], xmm2         ; save c

    ret

;------------------------------------------------------------------------------
;                         rdi               rsi              rdx
; void MulI32b_avx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

global _MulI32b_avx
_MulI32b_avx:

    vmovdqa     xmm0, [rsi]     ; xmm0 = a
    vmovdqa     xmm1, [rdx]     ; xmm1 = b

    ; Packed Multiply Signed Doubleword to Quadword
    vpmuldq      xmm2, xmm0, xmm1    ; packed mul - a*b even dwords
    ; Packed Shift Right Logical Double Quadword
    vpsrldq      xmm3, xmm0, 4       ; shift a_vals right 4 bytes
    vpsrldq      xmm4, xmm1, 4       ; shift b_vals right 4 bytes
    vpmuldq      xmm5, xmm3, xmm4    ; packed mul - a & b odd dwords
    ; Extract Packed Quadword
    vpextrq      [rdi], xmm2, 0     ; save quadword product 0
    vpextrq      [rdi+8], xmm5, 0   ; save qword product 1
    vpextrq      [rdi+16], xmm2, 1  ; save qword product 2
    vpextrq      [rdi+24], xmm5, 1  ; save qword prodcut 3

    ret
