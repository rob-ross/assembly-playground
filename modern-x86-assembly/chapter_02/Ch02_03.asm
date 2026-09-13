;-------------------------------------------------
;               Ch02_03.asm
;-------------------------------------------------
;
; extern "C" int IntegerShift_(
;   unsigned int a,      ; edi
;   unsigned int count,  ; esi
;   unsigned* a_shl,     ; rdx
;   unsigned* a_shr      ; rcx  ; copy rcx to r10, as we need the cl register for shr/shl
;   ) -> returns int eax
;
; Returns:  0 = error (if count >= 32), 1 = success
;


; MS Vs System V calling conventions
;       MS: 1. ECX, 2. EDX, 3. R8D, 4. R9D,               returns in EAX
; System V: 1. EDI, 2. ESI, 3. EDX, 4. ECX, 5. r8, 6. r9  returns in EAX

segment .text
global _IntegerShift_

_IntegerShift_:
    xor eax, eax    ; return value, init to 0
    cmp ESI, 31     ;compare count against 31
    ja InvalidCount ;jump if count > 31

    mov r10, rcx   ; save value of a_shr in r10
    mov ecx, esi    ; load count value into ecx

    mov  eax, edi   ;eax = a
    shl  eax, cl    ;eax = a << count;
    mov [rdx], eax  ;save result

    shr edi, cl
    mov [r10], edi

    mov eax, 1

InvalidCount:
    ret
