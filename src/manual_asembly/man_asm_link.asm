;------------------------------------------------------------------------------
; man_asm_link.asm
; Created by Rob Ross on 9/29/26.
;
; Assemble:
;   nasm -f macho64 man_asm_link.asm -o test1.o
;
; to assemble with debug info:
;   nasm -g -F dwarf -f mach64 man_asm_link.asm -o test1
;
; Link:
;   ld -e _main -platform_version macos 13.0 14.8 -syslibroot "$SDKROOT" test1.o -o test1 -lSystem
;
; Check disassembly:
;   objdump -d test1
;
; Dump content of the TEXT section:
;   otool -t test1
;
; Debug:
;   lldb ./test1
;   b main ; sets a breakpoint at main
;   run
;   register read
;------------------------------------------------------------------------------

default rel

align 16
section .data

    ; Using backquotes lets you embed standard C escape strings directly.
    ; This automatically appends a newline (\n) and a null terminator (\0).
    str1: db `hello world!\n\0`

    ; Equate macro: calculates the length of 'str1' by subtracting
    ; the start address of 'str1' from the current memory location ($)
    str1_len: equ $ - str1 - 1 ; -1 so we don't count the null termiator



section .text
    global _main

align 16
_main:
    sub rsp, 8  ; align

    mov rax, 0x2000004     ; System call `write` == 4
    mov rdi, 1              ; FD for stdout
    lea rsi, [str1]     ; The address of hello_word string
    mov rdx, 27             ; The number of bytes to write
    syscall                 ; Invoke the kernel
    mov rax, 0x2000001       ; System call number for exit == 1
    mov rdi, 0              ; Exit success == 0


    syscall                 ; invoke the kernel
