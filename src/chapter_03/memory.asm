; memory.asm
;
; ./build2.sh src/chapter_03/memory
; Make list file
; nasm -g -f macho64 memory.asm -l memory.list
segment .data
a   dd 4
b   dd 4.4
c   times 10 dd 0
d   dw 1, 2
e   db 0xfb
f   db "hello world", 0
segment .bss
g   resd 1      ; resd = reserve double word (32 bits)
h   resd 10     ; reserve 10 double words
i   resb 100    ; reserve 100 bytes
 segment .text
    global _main ; tell linker about main
_main:
    push rbp ; set up a stack frame
    mov rbp, rsp ; rbp points to stack frame
    sub rsp, 16 ; leave some room for locals
                ; rsp on a 16 byte boundary
    xor eax, eax ; rax = 0 for return value
    leave
    ret
