
;-------------------------------------------------
;               Ch02_02.asm
;-------------------------------------------------
; extern "C" unsigned int IntegerLogical_(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern _g_Val1 ;external doubleword (32-bit) value

section .text
global _IntegerLogical_
_IntegerLogical_:
;MS Vs System V calling conventions
;      MS: 1. ECX, 2. EDX, 3. R8D, 4. R9D,               returns in EAX
;System V: 1. EDI, 2. ESI, 3. EDX, 4. ECX, 5. r8, 6. r9  returns in EAX

; Calculate (((a & b) | c ) ^ d) + g_Val1
        and EDI,ESI
        or  EDI,EDX
        xor EDI,ECX
        add EDI,[ rel _g_Val1]
        mov eax,EDI
        ret
