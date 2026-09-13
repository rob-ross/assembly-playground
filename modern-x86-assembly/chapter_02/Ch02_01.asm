;-------------------------------------------------
;               Ch02_01.asm
;-------------------------------------------------
; extern "C" int IntegerAddSub_(int a, int b, int c, int d);
section .text

global _IntegerAddSub_

_IntegerAddSub_:
; Calculate a + b + c - d
; MS uses 1. ECX, 2. EDX, 3. R8D, and 4. R9D registers,, returns in EAX
; System V uses 1. rdi, 2. rsi, 3. rdx, 4. rcx, 5. r8, 6. r9
        mov eax,edi     ; eax = a
        add eax,esi     ; eax = a +b
        add eax,edx     ; eax = a +b+ c
        sub eax,ecx     ; eax = a +b+c- d

        ret             ;return result to caller

