
;-------------------------------------------------
;               Ch02_04.asm
;-------------------------------------------------
;
; extern "C" int IntegerMulDiv_(
;    int a,     = edi
;    int b,     = esi   ; divisor
;    int* prod, = edx
;    int* quo,  = ecx
;    int* rem   = r8d
; ) -> int ;
;
; Returns:      0 = error (divisor equals zero), 1 = success
;


; MS Vs System V calling conventions
;       MS: 1. ECX, 2. EDX, 3. R8D, 4. R9D,               returns in EAX
; System V: 1. EDI, 2. ESI, 3. EDX, 4. ECX, 5. r8, 6. r9  returns in EAX

section .text
global _IntegerMulDiv_

_IntegerMulDiv_:
; Make sure the divisor is not zero
    mov eax, esi        ; eax = b
    or  eax, eax        ; logical OR sets status flags
    jz  InvalidDivisor  ; jump if b is zero

; Calculate product and save result
    mov r10, rdx        ; save prod pointer, rdx used by multiply
    imul eax, edi       ; eax = a * b : EDX:EAX = a * b
    mov  [r10], eax     ; save product.

; Calculate quotient and remainder, save results
;    mov r10d, esi      ; r10d = b
    mov eax, edi        ; eax = a
    cdq                 ; edx:eax contains 64-bit dividend
    idiv esi            ; eax = quotient, edx = remainder

    mov [rcx],eax       ; save quotient
;    mov rax,[rsp+40]   ; rax = 'rem'
    mov rax, r8
    mov [rax], edx      ; save remainder
    mov eax,1           ; set success return code

InvalidDivisor:
    ret
