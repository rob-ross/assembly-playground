;------------------------------------------------------------------------------
; Ch07_01.asm
; Created by Rob Ross on 9/29/26.
;
;------------------------------------------------------------------------------

default rel

NSE     equ 8                                   ;num_simd_elements

section .text

;------------------------------------------------------------------------------
;                     rdi             rsi             rdx       rcx
; void CalcZ_avx(float* z, const float* x, const float* y, size_t n);
;------------------------------------------------------------------------------

global _CalcZ_avx
_CalcZ_avx:
    test    rcx,    rcx     ; n == 0?
    jz      .Done           ; jump if yes

; Initialize
    mov     rax,    -1      ; rax = rray offset for Loop2
    cmp     rcx,    NSE     ; n < NSE?
    jb      .Loop2          ; jump if yes
    mov     rax,    -NSE    ; rax = array offset for Loop1

; Calculate z[i:i+7] = x[i:i+7] + y[i:i+7]
.Loop1:
    add     rax,    NSE                 ; update offset for next SIMD group
    vmovups ymm0,   [rsi+rax*4]         ; ymm0 = x[i:i+7]
    vaddps  ymm1,   ymm0, [rdx+rax*4]   ; ymm1 = x[i:i+7] +  y[i:i=7]
    vmovups [rdi+rax*4], ymm1           ; save z[i:i+7]

    sub     rcx,    NSE                 ; n -= NSE
    cmp     rcx,    NSE                 ; n >= NSE?
    jae     .Loop1                      ; jump if yes

    test    rcx,    rcx                 ; n == 0?
    jz      .Done                       ; jump if yes
    add     rax,    NSE-1               ; adjust offset for start of Loop2

; 1-7 values are left in array
; Calculate z[i] = x[i] + y[i] (num residual elements = [1, NSE - 1])
.Loop2:
    add     rax,    1                   ; i += 1
    vmovss  xmm0,   [rsi+rax*4]         ; xmm0 = x[i]
    vaddss  xmm1,   xmm0, [rdx+rax*4]   ; xmm1 = x[i] + y[i]
    vmovss  [rdi+rax*4], xmm1           ; save z[i]

    sub     rcx,    1                   ; n -= 1
    jnz     .Loop2                      ; repeat Loop2 until done

.Done:
    vzeroupper              ; clear upper bits of ymm regs
    ret
