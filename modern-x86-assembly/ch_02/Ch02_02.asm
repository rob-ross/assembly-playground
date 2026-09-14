;------------------------------------------------------------------------------
; Ch02_02_fasm.asm
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; unsigned int BitOpsU32_a(unsigned int a, unsigned int b,, unsigned int c,
;unsigned int d);
;------------------------------------------------------------------------------
section .text
global _BitOpsU32_a
_BitOpsU32_a:
    ; Calculate ~(((a & b) | c ) ^ d)
    and edi,esi     ;edi = a & b
    or edi,edx      ;edi = (a & b) | c
    xor edi,ecx     ;edi = ((a & b) | c) ^ d
    not edi         ;edi = ~(((a & b) | c ) ^ d)
    mov eax,edi     ;eax = final result
    ret             ;return to caller
