; Program: exit
;
; Executes the exit system call
;
; No input
;
; Output: only the exit status
; sets exit status to 0
; $? in the shell
;
segment .text
global _main
_main:
    mov eax,0x2000001 ; macos exit syscall number
    mov rdi, 22 ; Exit code (0-255). Only lower 8 bits are read by OS.
    syscall ; execute a system call
