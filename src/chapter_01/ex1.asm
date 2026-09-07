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
    mov edi,0 ; the status value to return
    syscall ; execute a system call
