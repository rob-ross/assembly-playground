;-------------------------------------------------
;               Ch02_05.asm
;-------------------------------------------------


section .text
global _IntegerMul_

_IntegerMul_:
; extern "C" int64_t IntegerMul_(
;    int8_t  a, = dil
;    int16_t b, = si
;    int32_t c, = edx
;    int64_t d, = rcx
;    int8_t  e, = r8b
;    int16_t f, = r9w
; ------------------------------------
;       stck variables
;    int32_t g, -> dword [rsp + 8]
;    int64_t h  -> qword [rsp + 16]
;) -> int64_t;



; Calculate a * b * c * d
    movsx rax, dil   ;rax = sign_extend(a)
    movsx rsi, si    ;rsi = sign_extend(b)
    imul  rax, rsi   ;rax = a * b ;
    movsx rdx, edx   ;rdx = sign_extend(c)
    imul  rdx, rcx   ;rdx = c * d
    imul  rax, rdx   ;rax = a*b*c* d

; Calculate e * f * g * h
    movsx r8, r8b      ;r8 = sign_extend(e)
    movsx r9, r9w      ;r9 = sign_extend(f)
    imul  r8, r9       ;r8 = e * f

; must load g and h from stack
    ; g is the 7th integer argument
    ; h is the 8th integer argument
    movsxd r10, dword [rsp + 8]    ; r10 = sign-extended int32_t g
    mov    r11, qword [rsp + 16]   ; r11 = int64_t h
    imul   r10, r11                ; r10 = g * h
    imul   r8, r10                 ; r8  = e * f * g * h

; Compute the final product
        imul rax,r8    ;rax = final product
        ret

global _UnsignedIntegerDiv_
_UnsignedIntegerDiv_:
; extern "C" int UnsignedIntegerDiv_(
;        uint8_t  a, -> dil
;        uint16_t b, -> si
;        uint32_t c, -> edx
;        uint64_t d, -> rcx
;        uint8_t  e, -> r8b
;        uint16_t f, -> r9w
; -------------------------
;        stack variables:
;        uint32_t g, -> dword [rsp+8]
;        uint64_t h, -> qword [rsp+16]
;        uint64_t* quo, -> qword [rsp+24]
;        uint64_t* rem  -> qword [rsp+32]
; );

; MS Vs System V calling conventions
;       MS: 1. ECX, 2. EDX, 3. R8D, 4. R9D,               returns in EAX
; System V: 1. EDI, 2. ESI, 3. EDX, 4. ECX, 5. r8, 6. r9  returns in EAX

; Calculate a + b + c + d
    movzx rax, dil  ; rax := zero_extend(a)
    movzx rsi, si   ; rsi := zero_extend(b)
    add   rax, rsi  ; rax := a + b
    movzx rdx, edx  ; rdx := zero_extend(c)
    add   rdx, rcx  ; rdx := c + d
    add   rax, rdx  ; rax := a + b + c + d

; Calculate e + f + g + h
    movzx r8, r8b    ; rdx := zero_extend(e)
    movzx rcx, r9w   ; rcx := zero_extend(f)
    add   r8, rcx    ; rdx := e + f
    movzx r10, dword [rsp+8]     ; r10 := zero_extend(g)
    add   r10,  [rsp+16]    ; r10 := g + h;
    add   r8, r10           ; r8 := e + f + g + h

    jnz   DivOk             ; jump if divisor is not zero
    xor   eax, eax          ; set error return code 0
    jmp   Done

; Calculate (a + b + c + d) / (e + f + g + h)
DivOk:
    xor rdx,rdx         ; zero out since div implicitly uses it as part of the dividend
    div r8              ; RDX:RAX := unsigned divide RDX:RAX / r8
    mov rdi, [rsp+24]   ; move address of return argument `quo` into rdi
    mov [rdi], rax      ; save quotient: *quo := rax
    mov rdi, [rsp+32]   ; rdi := rem
    mov [rdi], rdx      ; save remainder: *rem = rdx

    mov eax, 1          ; set success return code
Done:
    ret

