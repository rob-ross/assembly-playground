;------------------------------------------------------------------------------
; Ch09_01.asm
; Created by Rob Ross on 10/16/26.
;
;------------------------------------------------------------------------------

default rel


section .rodata

F64_AbsMask  dq 07fffffffffffffffh      ; data quadword, 8 bytes, 64 bits
F32_AbsMask  dd 07fffffffh              ; data dword,    4 bytes, 32 bits


section .text

;------------------------------------------------------------------------------
; void PackedMathF32_avx(
;   YmmVal* c,          -> rdi
;   const YmmVal* a,    -> rsi
;   const YmmVal* b     -> rdx
; );
;------------------------------------------------------------------------------
global _PackedMathF32_avx
_PackedMathF32_avx:

    vmovaps     ymm0, [rsi]     ; ymm0 = a
    vmovaps     ymm1, [rdx]     ; ymm1 = b

    vaddps      ymm2, ymm0, ymm1   ; SPFP addition
    vmovaps     [rdi], ymm2         ; [rdi] = a + b

    vsubps      ymm2, ymm0, ymm1    ; SPFP subtraction
    vmovaps     [rdi+32], ymm2      ; [rdi+32] = a - b

    vmulps      ymm2, ymm0, ymm1    ; SPFP multiplication
    vmovaps     [rdi+64], ymm2      ; [rdi+64] = a * b

    vdivps      ymm2, ymm0, ymm1    ; SPFP division
    vmovaps     [rdi+96], ymm2      ; [rdi+96] = a / b

    vminps      ymm2, ymm0, ymm1    ; SPFP min
    vmovaps     [rdi+128], ymm2     ; [rdi+128] = min(a,b)

    vmaxps      ymm2, ymm0, ymm1    ; SPFP max
    vmovaps     [rdi+160], ymm2     ; [rdi+160] = max(a,b)

    vsqrtps     ymm2, ymm0          ; SPFP square root
    vmovaps     [rdi+192], ymm2     ; [rdi+192] = sqrt(a)

    vbroadcastss    ymm3, [F32_AbsMask]    ; load abs mask
    vandps          ymm2, ymm3, ymm1        ; SPFP abs(b) ; masks off high-order bit
    vmovaps         [rdi+224], ymm2         ; [rdi+224] = abs(b)

    vzeroupper                       ; clear upper YMM2/ZMM bits
    ret


;------------------------------------------------------------------------------
; void PackedMathF64_avx(
;   YmmVal c[8],        ->rdi
;   const YmmVal* a,    ->rsi
;   const YmmVal* b     ->rdx
; );
;------------------------------------------------------------------------------
global _PackedMathF64_avx
_PackedMathF64_avx:


    ret
