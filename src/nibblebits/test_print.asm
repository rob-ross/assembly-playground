BITS 64
default rel

extern _printf
global _main

section .data
fmt db "%ld", 10, 0

section .text
align 16
_sum:
    ; executes here
    add rdi, rsi
    mov rax, rdi
    ret

align 16
_main:
    mov rdi, 50
    mov rsi, 20
    call _sum
    ; print the result
    lea rdi, [rel fmt]
    mov rsi, rax
    xor eax, eax    ; fast way to set eax to 0
    ; c functions expect first arg in rdi, second in rsi
    sub rsp, 8
    call _printf
    add rsp, 8

    xor eax, eax
    ret
