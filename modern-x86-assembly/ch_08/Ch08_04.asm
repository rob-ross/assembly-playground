;------------------------------------------------------------------------------
; Ch08_04.asm
; Created by Rob Ross on 10/13/26.
;
;------------------------------------------------------------------------------

default rel


section .text

;------------------------------------------------------------------------------
;                       rdi,             rsi,            edx
; void SllU16_avx(XmmVal* c, const XmmVal* a, uint32_t count);
;------------------------------------------------------------------------------
global _SllU16_avx
_SllU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 := a
    vmovd       xmm1, edx           ; xmm1[31:0] := count
    vpsllw      xmm2, xmm0, xmm1    ; xmm2 := a[i] << count ; each word in xmm0 is logical left-shifted by count
    vmovdqa     [rdi], xmm2         ; save result
    ret


;------------------------------------------------------------------------------
; void SrlU16_Aavx(XmmVal* c, const XmmVal* a, uint32_t count);
;------------------------------------------------------------------------------
global _SrlU16_avx
_SrlU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 = a
    vmovd       xmm1, edx           ; xmm1[31:0] = count
    vpsrlw      xmm2, xmm0, xmm1    ; xmm2 = a[i] >> count ; each word in xmm0 is logical right-shifted by count
    vmovdqa     [rdi], xmm2         ; save result
    ret


;------------------------------------------------------------------------------
; void SraU16_Aavx(XmmVal* c, const XmmVal* a, uint32_t count);
;------------------------------------------------------------------------------
global _SraU16_avx
_SraU16_avx:
    vmovdqa     xmm0, [rsi]         ; xmm0 = a
    vmovd       xmm1, edx           ; xmm1[31:0] = count
    vpsraw      xmm2, xmm0, xmm1    ; xmm2 = a[i] >> count; each word in xmm0 is arithmetic right-shifted by count
    vmovdqa     [rdi], xmm2         ; save result
    ret
