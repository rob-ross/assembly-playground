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
;   uint32_t n          -> rcx
; ) -> bool -> rax
;------------------------------------------------------------------------------
global _CalcMeanU8_avx
_CalcMeanU8_avx:

    ret
