;------------------------------------------------------------------------------
; Ch05_06.asm
; Created by Rob Ross on 9/27/26.
;
;------------------------------------------------------------------------------

default rel

section .text

;------------------------------------------------------------------------------
; bool ConvertScalar_avx(Uval* des, const Uval* src, CvtOp cvt_op, RC rc)
;------------------------------------------------------------------------------
global _ConvertScalar_avx
_ConvertScalar_avx:

; Make sure cvt_op is valid

    ret
