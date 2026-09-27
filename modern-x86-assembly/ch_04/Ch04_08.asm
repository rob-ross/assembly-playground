;------------------------------------------------------------------------------
; Ch04_08.asm
;------------------------------------------------------------------------------

default rel

; Test structure
struc TestStruct
.Val8:    resb  1
.PadA:    resb  7
.Val64:   resq  1
.Val16:   resw  1
.PadB     resb  2
.Val32:   resd  1
endstruc


section .text


;------------------------------------------------------------------------------
; int64_t SumStructVals_a(const TestStruct* ts);
;------------------------------------------------------------------------------
global _SumStructVals_a
_SumStructVals_a:

; Compute ts->Val8 + ts->Val16, note sign extensions to 32-bits
    movsx   eax, byte [rdi+TestStruct.Val8]
; when adding a register and memory, operands must be the same size. so this doesn't work:
;    add     eax, word [rdi+TestStruct.Val16]
; must move the word into a double word register to add to a double
    movsx   edx,  word [rdi+TestStruct.Val16]
    add     eax, edx

; Sign extend previous result to 64 bits
    movsxd   rax, eax
; Add ts->Val32 to sum
    movsxd  rdx, dword [rdi+TestStruct.Val32]
    add     rax, rdx
; Add ts->Val64 to sum
    add     rax, [rdi+TestStruct.Val64]

    ret
