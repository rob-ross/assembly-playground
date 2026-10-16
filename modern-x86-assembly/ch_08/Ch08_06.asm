;------------------------------------------------------------------------------
; Ch08_06.asm
; Created by Rob Ross on 10/14/26.
;
;------------------------------------------------------------------------------

default rel


NSE     equ 64                              ;num pixels per iteration of Loop1

section .text

;------------------------------------------------------------------------------
; bool CalcMeanU8_avx(
;   double* mean_x,     -> rdi
;   uint64_t* sum_x,    -> rsi
;   const uint8_t* x,   -> rdx
;   uint32_t n          -> ecx
; ) -> bool -> eax
;------------------------------------------------------------------------------
global _CalcMeanU8_avx
_CalcMeanU8_avx:
; Make sure n and x are valid
    test    ecx, ecx        ; is n == 0?
    jz      .BadArg         ; jump if yes

    test    ecx, 0x3F       ; is n even multiple of 64?
    jnz     .BadArg         ; jump if no

    test    ecx, 0x0F       ; is x aligned on a 16-byte boundary?
    jnz     .BadArg         ; jump if no

; Initialize
    vpxor   xmm5,   xmm5,   xmm5        ; packed sums (2 words)
    vpxor   xmm15,  xmm15,  xmm15       ; packed zero for size promotions
    mov     r10d,   ecx                 ; r10d = n ( for use in .Loop1
    ; subtracts increment unit from x pointer beore loop starts to avoid loop carried dependency
    sub     rdx,    NSE                 ; *x -= NSE

; Calculate sum of all pixels
.Loop1:
    add     rdx,    NSE                 ; rdx = &x[i]
    vpxor   xmm0,   xmm0,   xmm0        ; xmm0[127:0] = 0; initializes loop packed sums (16 words)
    vpxor   xmm1,   xmm1,   xmm1        ; xmm1 = 0

    vmovdqa    xmm2, [rdx]              ; xmm2 = x[i:i+15] ; loads next pixel block
    vpunpcklbw xmm3, xmm2, xmm15        ; promote x[i:i+7] to words
    vpaddw     xmm0, xmm0, xmm3         ; update sums[0:7]
    vpunpckhbw xmm4, xmm2, xmm15        ; promote x[i+8:i+15] to words
    vpaddw     xmm1, xmm1, xmm4         ; update sums[8:15]

    vmovdqa    xmm2, [rdx+16]           ; xmm2 = x[i+16:i+31] ; loads next pixel block
    vpunpcklbw xmm3, xmm2, xmm15        ; promote x[i+16:i+23] to words
    vpaddw     xmm0, xmm0, xmm3         ; update sums[0:7]
    vpunpckhbw xmm4, xmm2, xmm15        ; promote x[i+24:i+31] to words
    vpaddw     xmm1, xmm1, xmm4         ; update sums[8:15]

    vmovdqa    xmm2, [rdx+32]           ; xmm2 = x[i+32:i+47] ; loads next pixel block
    vpunpcklbw xmm3, xmm2, xmm15        ; promote x[i+32:i+39] to words
    vpaddw     xmm0, xmm0, xmm3         ; update sums[0:7]
    vpunpckhbw xmm4, xmm2, xmm15        ; promote x[i+40:i+47] to words
    vpaddw     xmm1, xmm1, xmm4         ; update sums[8:15]

    vmovdqa    xmm2, [rdx+48]           ; xmm2 = x[i+48:i+63] ; loads next pixel block
    vpunpcklbw xmm3, xmm2, xmm15        ; promote x[i+48:i+55] to words
    vpaddw     xmm0, xmm0, xmm3         ; update sums[0:7]
    vpunpckhbw xmm4, xmm2, xmm15        ; promote x[i+56:i+63] to words
    vpaddw     xmm1, xmm1, xmm4         ; update sums[8:15]

    vpaddw      xmm0, xmm0, xmm1        ; loop packed sums (8 words)
    vpunpcklwd  xmm1, xmm0, xmm15       ; promote loop packed sums to dwords
    vpunpckhwd  xmm2, xmm0, xmm15
    vpaddd      xmm3, xmm1, xmm2        ; loop packed sums (4 dwords)

    vpunpckldq  xmm0, xmm3, xmm15       ; promote loop packed sums to qwords
    vpunpckhdq  xmm1, xmm3, xmm15
    vpaddq      xmm5, xmm5, xmm0        ; updated packed sums (2 qwords)
    vpaddq      xmm5, xmm5, xmm1

    sub         r10d, NSE               ; n -= NSE
    jnz         .Loop1                  ; repeat until done

; Reduce packed sums (2 qwords) to single qword
    vpextrq     rax, xmm5, 0            ; rax = xmm5[63:0]
    vpextrq     r10, xmm5, 1            ; r10 = xmm5[127:64]
    add         rax, r10                ; rax = final pixel sum
    mov         [rsi], rax              ; save final pixel sum

; Calculate mean
    vcvtsi2sd   xmm0, xmm0, rax         ; convert sum to DPFP (dualprec float point)
    vcvtsi2sd   xmm1, xmm1, ecx         ; convert n to DPFP
    vdivsd      xmm2, xmm0, xmm1        ; mean = sum / n
    vmovsd      [rdi], xmm2             ; save mean

    mov        eax, 1                   ; set return value "true" success code
    ret

.BadArg:
    xor     eax, eax      ; set return value "false", error code
    ret
