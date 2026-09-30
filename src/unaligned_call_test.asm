;------------------------------------------------------------------------------
; unaligned_call_test.asm
; Created by Rob Ross on 9/29/26.
;
;------------------------------------------------------------------------------

default rel

section .data
    ; Define our double-precision float (8 bytes)
    my_float:    dq 3.14
    ; Format string containing a newline
    fmt_string:  db "The float is: %f", 10, 0

section .text
    global _main
    extern _printf

_main:
    ; --- STEP 1: ALIGN THE STACK ---
    ; Entering _main misaligns the stack by 8 bytes (due to the return address).
    ; We subtract 8 bytes from RSP to make it 16-byte aligned before calling printf.
    sub rsp, 8  ; crashes on Mac intel with segv if this is commented out!

    ; --- STEP 2: SET UP INT REGISTERS ---
    ; Move the address of the format string into the 1st integer argument register
    lea rdi, [rel fmt_string]

    ; --- STEP 3: SET UP XMM REGISTERS ---
    ; Move the 64-bit float (double) into the 1st vector argument register
    movsd xmm0, [rel my_float]

    ; --- STEP 4: SET THE VARIADIC COUNT ---
    ; Inform printf that exactly 1 XMM register is being used
    mov rax, 1

    ; --- STEP 5: CALL THE C LIBRARY ---
    call _printf

    ; --- STEP 6: CLEAN UP AND EXIT ---
    ; Restore the stack pointer to what it was before our alignment adjustment
    add rsp, 8

    ; Return 0 from main
    mov rax, 0
    ret
