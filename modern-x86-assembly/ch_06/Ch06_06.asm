;------------------------------------------------------------------------------
; Ch06_06.asm
; Created by Rob Ross on 9/28/26.
;
;------------------------------------------------------------------------------

default rel

; RBP offsets for temp variables on stack
TEMP_A      equ -8
TEMP_B      equ -16
TEMP_C      equ -24
TEMP_D      equ -32

STK_LOCAL   equ 32      ;storage space allocated on stack for temp variables

; RBP offsets for stack arguments
ARG_G   equ 32
ARG_H   equ 40

section .text

;------------------------------------------------------------------------------
;   rax
; int64_t AddIntegers_a(
;   int8_t  a,  rdi
;   int16_t b,  rsi
;   int32_t c,  rdx
;   int64_t d,  rcx
;   int8_t  e,  r8
;   int16_t f,  r9
;   int32_t g,  rsp+8
;   int64_t h   rsp+16
; );
;------------------------------------------------------------------------------

global _AddIntegers_a
_AddIntegers_a:

; Function prologue
    ; at start of function, the stack pointer points to the return address of the callee
    push    rbp     ; save caller's rbp as we are about to change it
    push    r14     ; save non-volatile registers. For demonstration purposes
    push    r15
    mov     rbp, rsp            ; create the new stack frame
    sub     rsp, STK_LOCAL      ; allocate STK_LOCAL bytes on stack

; Sign-extend and save a, b, c, and d on the stack
    movsx   rdi, dil            ; rdi = a
    mov     [rbp+TEMP_A], rdi   ; save sign-extended a
    movsx   rsi, si             ; rsi = b
    mov     [rbp+TEMP_B], rsi   ; save sign-extended b
    movsxd  rdx, edx            ; rcx = c
    mov     [rbp+TEMP_C], rdx   ; save sign-extended c
    mov     [rbp+TEMP_D], rcx   ; save d

; Sign-extend e, f, and g
    movsx   rcx, r8b            ; rcx = e
    movsx   rdx, r9w            ; rdx = f
    movsxd  r8, [rbp+ARG_G]     ;  r8 = g
    mov     r9, [rbp+ARG_H]     ;  r9 = h

; calculate a + b + c + d + e + f + g + h
    add     rcx, [rbp+TEMP_A]            ; rdi = a + e
    add     rdx, [rbp+TEMP_B]            ; rdx = f + b
    add     r8,  [rbp+TEMP_C]            ;  r8 = g + c
    add     r9,  [rbp+TEMP_D]            ;  r9 = h + d
    add     rcx, rdx                     ; rcx = a + e + f + b
    add     r8, r9                       ;  r8 = g + c + h + d
    add     rcx, r8                      ; rcx = e + a + f + b + g + c + h + d
    mov     rax, rcx                     ; rax = final sum

; Function epilogue
    mov     rsp, rbp        ;release local storage
    pop     r15
    pop     r14
    pop     rbp             ;restore non-volatile GPRs
    ret
