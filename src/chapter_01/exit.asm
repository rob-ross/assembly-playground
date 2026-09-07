; Program: exit
;
; Executes the exit system call
;
; No input
;
; Output: only the exit status
; $? in the shell
;
segment .text
global _main
_main:
    mov eax,0x2000001 ; 60 is the exit syscall number
    ; 0x2000001 for OS X
    mov edi,5 ; the status value to return
    syscall ; execute a system call
end: ; end is not used in NASM as a directive
