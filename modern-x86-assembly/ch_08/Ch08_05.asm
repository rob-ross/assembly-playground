;------------------------------------------------------------------------------
; Ch08_05.asm
; Created by Rob Ross on 10/14/26.
;
;------------------------------------------------------------------------------

default rel


NSE     equ 16                              ; num_simd_elements
                                            ; (num pixels per iteration of Loop1)

section .text

;------------------------------------------------------------------------------
; rax
; bool CalcMinMaxU8_avx(
;   uint8_t* x_min,     -> rdi
;   uint8_t* x_max,     -> rsi
;   const uint8_t* x,   -> rdx
;   size_t n            -> rcx
; ) -> rax (bool);
;------------------------------------------------------------------------------
global _CalcMinMaxU8_avx
_CalcMinMaxU8_avx:

; Make sure n and x are valid
    test    rcx, rcx        ; is n == 0?
    jz      .BadArg         ; jump if yes

    ; n must be a multiple of 16 (NSE)
    test    rcx, 0x0F       ; is n % 16 == 0?
    jnz     .BarArg         ; jump if no

    test    rdx, 0x0F       ; is x aligned to 16 byte boundary?
    jnz     .BarArg         ; jump if no


; Initialize packed min and max values
    vpcmpeqb    xmm4, xmm4, xmm4    ; packed minimums (all 0xFF)
    vpxor       xmm5, xmm5, xmm5    ; packed maximums (all 0x00)
    sub         rdx,  NSE           ; adjust rdx for .Loop1

; Find packed min-max values in x[]
.Loop1:
    add         rdx, NSE            ; rdx points to x[i:i+NSE-1]
    vmovdqa     xmm0, [rdx]         ; xmm0 = block of 16 pixels
    vpminub     xmm4, xmm4, xmm0    ; update packed min values
    vpmaxub     xmm5, xmm5, xmm0    ; update packed max values

    sub         rcx, NSE            ; n -= NSE
    jnz         .Loop1              ; repeat until n == 0


; Reduce packed min values
    vpsrldq     xmm0, xmm4, 8       ; logical right shift xmm4 8 bytes
    vpminub     xmm0, xmm0, xmm4    ; xmm0[63:0] = final 8 min vals

; Reduce packed max values



.BadArg:
    xor eax,eax                         ;set error return code
    ret
