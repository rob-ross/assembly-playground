;------------------------------------------------------------------------------
; Ch03_01.asm
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; int32_t SumValsI32_a(
;       int32_t a,  -> edi
;       int32_t b,  -> esi
;       int32_t c,  -> edx
;       int32_t d,  -> ecx
;       int32_t e,  -> r8d
;       int32_t f,  -> r9d
; ----------------------------
; stack:
;       int32_t g, [rsp + 8]
;       int32_t h  [rsp + 16]  
;       );
;------------------------------------------------------------------------------
section .text
global _SumValsI32_a
_SumValsI32_a:
;Calculate a + b,  c + d
    add edi, esi    ; edi := a + b
    add edx, ecx    ; edx := c + d

; Calculate e + f, g + h
    add r8d, r9d            ; r8d := e + f
    mov eax, [rsp + 8]      ; eax := g
    add eax, [rsp + 16]     ; eax := g + h

    add edi, edx            ; edi := a + b + c + d
    add eax, r8d            ; eax := e + f + g + h

    add eax, edi            ; eax = a + b + c + d + e + f + g + h

    ret

;------------------------------------------------------------------------------
; uint64_t MulValsU64_a(
;        uint64_t a,    -> rdi
;        uint64_t b,    -> rsi
;        uint64_t c,    -> rdx
;        uint64_t d,    -> rcx
;        uint64_t e,    -> r8
;        uint64_t f,    -> r9
; ---------------------
;   stack:
;        uint64_t g,    -> [rsp + 8]
;        uint64_t h     -> [rsp + 16]
;        );
;------------------------------------------------------------------------------
global _MulValsU64_a
_MulValsU64_a:
; Calculate a * b * c * d * e * f * g * h
    mov r10,rdx             ; r10 := c ; save copy of c, we need rdx for the multiply op
    mov rax, rdi            ; rax := a
    mul rsi                 ; rax := a * b
    mul r10                 ; rax := a * b * c
    mul rcx                 ; rax := a * b * c * d
    mul r8                  ; rax := a * b * c * d * e
    mul r9                  ; rax := a * b * c * d * e * f
    mul qword [rsp + 8]     ; rax := a * b * c * d * e * f * g
    mul qword [rsp + 16]    ; rax := a * b * c * d * e * f * g * h
    ret


;mov rax,rdi     ;rax = a
;mul rsi         ;rax = a * b
;mul r10         ;rax = a * b * c
;mul rcx         ;rax = a * b * c * d
;mul r8          ;rax = a * b * c * d * e
;mul r9          ;rax = a * b * c * d * e * f
;mul qword [rsp+8]       ;rax = a * b * c * d * e * f * g
;mul qword [rsp+16]      ;rax = final product
;ret
