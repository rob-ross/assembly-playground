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

; Sign extend previous result to 64 bits

; Add ts->Val32 to sum

; Add ts->Val64 to sum


    ret
