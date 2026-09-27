;------------------------------------------------------------------------------
; Ch05_02.asm
;------------------------------------------------------------------------------
default rel

section .rodata
F32_3p0     dd  3.0

section .text

extern _g_F32_PI    ; float
;------------------------------------------------------------------------------
;                               rdi        rsi      xmm0    xmm1
; void CalcConeVolSA_avx(float* vol, float* sa, float r, float h);
;------------------------------------------------------------------------------
global _CalcConeVolSA_avx
_CalcConeVolSA_avx:

; Calculate vol = pi * r * r * h / 3.0f;
    vmulss  xmm2, xmm0, xmm0            ; xmm2 := r * r;
    vmulss  xmm3, xmm2, [_g_F32_PI]     ; xmm3 := r * r * pi
    vmulss  xmm4, xmm3, xmm1            ; xmm4 := r * r * pi * h
    vdivss  xmm5, xmm4, [F32_3p0]       ; xmm5 := r * r * pi * h / 3.0
; dword is redundant below. the second 's' in `vmovss` indicates a single precision value, i.e. a double word (4 bytes)
    vmovss  dword [rdi], xmm5           ; save volume

; Calculate sa = pi * r * (r + sqrt(r * r + h * h));
    vmulss  xmm3, xmm1, xmm1            ; xmm3 := h * h
    vaddss  xmm4, xmm2, xmm3            ; xmm4 := r * r + h * h
    vsqrtss xmm5, xmm4, xmm4            ; xmm5 := sqrt(r * r + h * h)
    vaddss  xmm5, xmm0, xmm5            ; xmm5 := r + sqrt(r * r + h * h)
    vmulss  xmm2, xmm0, [_g_F32_PI]     ; xmm2 := r * pi
    vmulss  xmm5, xmm2, xmm5            ; xmm5 := r * pi * (r + sqrt( r * r + h * h) )
    vmovss  [rsi], xmm5                 ; save surface area

    ret
