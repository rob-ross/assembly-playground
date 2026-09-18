;------------------------------------------------------------------------------
; Ch03_04.asm
;------------------------------------------------------------------------------

default rel

;------------------------------------------------------------------------------
; int SignedMin1_a(int a, int b, int c);
;------------------------------------------------------------------------------

section .text

global _SignedMin1_a
_SignedMin1_a:
    mov eax, esi
    cmp eax, edi    ; compare a and b
    jle F1          ; jump if a <= b
    mov eax, edi    ; eax := b
F1:
    ; here we now have min(a,b) in eax
    cmp eax, edx    ; compare min(a,b) and c
    jle F2          ; jump if min(a,b) <= c
    mov eax, edx    ; eax := c
F2:
    ret


;------------------------------------------------------------------------------
; int SignedMin2_a(int a, int b, int c);
;------------------------------------------------------------------------------
global _SignedMin2_a
_SignedMin2_a:
    cmp     edi, esi
    cmovg   edi, esi    ; if a > b, edi := b
    cmp     edi, edx
    cmovg   edi, edx    ; if min(a,b) > c, edi := c
    mov     eax, edi
    ret

;------------------------------------------------------------------------------
; int SignedMax1_a(int a, int b, int c);
;------------------------------------------------------------------------------
global _SignedMax1_a
_SignedMax1_a:
    cmp     edi, esi
    jge     F3          ; jump if a >= b
    mov     edi, esi    ; edi := b
F3:
    cmp     edi, edx
    jge     F4          ; jump if max(a,b) >= c
    mov     edi, edx    ; edi := c
F4:
    mov     eax, edi
    ret

;------------------------------------------------------------------------------
; int SignedMax2_a(int a, int b, int c);
;------------------------------------------------------------------------------
global _SignedMax2_a
_SignedMax2_a:
    cmp     edi, esi
    cmovl   edi, esi    ; if a < b, edi := b
    cmp     edi, edx
    cmovl   edi, edx    ; if max(a,b) < c, edi := c
    mov     eax, edi
    ret
