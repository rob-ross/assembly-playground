;------------------------------------------------------------------------------
; Ch05_07.asm
; Created by Rob Ross on 9/27/26.
;
;------------------------------------------------------------------------------

default rel


section .text

;------------------------------------------------------------------------------
; rax                          rdi              rsi       rdx
; bool CalcMeanF64_avx(double* mean, const double* x, size_t n);
;------------------------------------------------------------------------------

global _CalcMeanF64_avx
_CalcMeanF64_avx:

; Make sure n is valid, must be > 1
    cmp     rdx, 1      ; is rdx > 1?
    jbe    .BadN        ; return error

; Initialize
    vxorpd  xmm0, xmm0, xmm0    ; sum := 0, clear xmm0
    mov     rcx, -1     ; i := -1, initialize loop variable

.Loop:
    add     rcx, 1      ; i += 1
    vaddsd  xmm0, xmm0, [rsi+rcx*8]   ; sum += x[i]
    cmp     rcx, rdx    ; is i < n?, is rcx < rdx?
    jb     .Loop        ; if true continue loop

; Calculate and save the mean
    vcvtsi2sd   xmm1, xmm1, rdx     ; xmm1 := n
    vdivsd      xmm1, xmm0, xmm1    ; mean := sum / n
    vmovsd      [rdi], xmm1         ; save result
    mov         eax, 1              ; set return value "true"
    ret

.BadN:
    xor     eax, eax    ; set error return to 0, "false"
    ret

;------------------------------------------------------------------------------
;  rax                             rdi             rsi        rdx         xmm0
; bool CalcStDevF64_avx(double* st_dev, const double* x, size_t n, double mean);
;------------------------------------------------------------------------------

global _CalcStDevF64_avx
_CalcStDevF64_avx:

; Make sure n is valid
    cmp     rdx, 1      ; is n <= 1?
    jbe     .BadN       ; jmp to .BadN if <= 1

; Initialize
    ; xmm0 containst the mean
    vxorpd  xmm1, xmm1, xmm1    ; double sum_squares = 0.0;
    mov    rcx, -1              ; i := -1

.Loop:
    add     rcx, 1                      ; i += 1
    vsubsd  xmm2, xmm0, [rsi+rcx*8 ]    ; temp := x[i] - mean
    vmulsd  xmm2, xmm2, xmm2            ; temp *= temp
    vaddsd  xmm1, xmm1, xmm2            ; sum += temp
    cmp     rcx, rdx                    ; is i < n?
    jb      .Loop                       ; if so, continue loop

; Calculate and save the standard deviation
    ; here rcx == n,
    sub     rcx, 1      ; rcx := n - 1
    vcvtsi2sd   xmm2, xmm2, rcx     ; convert (n-1) to double
    vdivsd      xmm2, xmm1, xmm2    ; temp :=  sum_squares / (n-1)
    vsqrtsd     xmm1, xmm1, xmm2    ; xmm1 := sqrt(temp)
    vmovsd      [rdi], xmm1         ; save result

    mov         eax, 1              ; return success "true"
    ret

.BadN:
    xor     eax, eax    ; set error return to 0, "false"
    ret
