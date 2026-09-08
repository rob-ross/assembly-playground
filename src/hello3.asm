; hello3.asm

BITS 64
default rel

section .data
msg: db "Hello World", 0x0A ; message + newline

section .text
global _main

_main:
    ; write(1, msg, len)
    mov rax, 0x2000004   ; sys_write
    mov rdi, 1  ; file descriptor 1 = stdout
    lea rsi, [rel msg]  ; pointer to message
    mov rdx, 12         ; 12 byts to write to stdout
    syscall

    ; exit(0)
    mov rax, 0x2000001 ; sys_exit
    xor rdi, rdi      ; status 0
    syscall

