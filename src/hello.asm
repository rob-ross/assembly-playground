global _main

section .text
_main:
    ; System call: write(fd, buf, count)
    mov     rax, 0x2000004      ; macOS system call for write
    mov     rdi, 1              ; File descriptor 1 = stdout
    lea     rsi, [rel message]  ; Pointer to message (position-independent)
    mov     rdx, message_len    ; Length of message
    syscall

    ; System call: exit(status)
    mov     rax, 0x2000001      ; macOS system call for exit
    mov     rdi, 0              ; Exit code 0
    syscall

section .data
message:     db "Hello, 64-bit Assembly in CLion!", 0x0A
message_len: equ $ - message
