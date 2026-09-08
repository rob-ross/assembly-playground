; test_registers.asm
;
;   test loading values into parts of a register to see how it affects the higher order bytes

BITS 64
default rel
global _main

section .text
align 16
_main:
    nop
    nop
    mov     rax, max_ulong   ; try to load constant max_ulong into rax

    mov     rbx, max_ulong        ; set all bits
    ; because we specify rbx, 8 bytes are read from the address at max_uint_a, which reads past
    ; the intended 4 bytes. We need to use ebx to read only 4 bytes into the register
    mov     rbx, [ rel max_uint_a]  ; copies 4 bytes from max_uint_a, and 4 bytes from max_uint_b

    ; writing to ebx zeroes out high 4 bytes
    mov     rbx, max_ulong          ; set all bits
    mov     ebx, [ rel max_uint_a]  ; write just 4 bytes, zeros out high 4 bytes.

    ; to just write to the 4 low bytes or rbx and keep the high 4 bytes,
    ; we need a temp register: rax
    mov     rbx, max_ulong          ; set all bits

    mov     eax, [ rel max_uint_a]  ; high 4 of rax are zeroed
    and     rbx, mask_q_h4          ; low 4 bytes are zeroed
    or      rbx, rax                ; low 4 bytes of rax get copied to rbx, upper 4 bytes of rbx unaffected

attempt_4:
; the previous attempt did not work. `and r64 immediate` only works on the low 32 bits and sign-extends to 64 bits.
; so all of rbx is set to 0. To mask the full 64 bits we need to use a full register
    mov     rbx, max_ulong          ; set all bits
    mov     rcx, mask_q_h4          ; load mask into rcx
    mov     eax, [ rel max_uint_a]  ; high 4 of rax are zeroed, low 4 bytes are what we want to end up in rbx
    and     rbx, rcx                ; keep high 4 bytes
    or      rbx, rax                ; combine high 4 bytes of original rbx, and low 4 bytes of new value from eax.
; and this time it works!!!



    ; System call: exit(status)
    mov     rax, 0x2000001      ; macos system call for exit
    mov     rdi, 0              ; Exit code 0
    syscall


section .data
align 16
max_ulong   equ 0xFFFFFFFFFFFFFFFF
max_uint_a  dd  0xA4A3A2A1
max_uint_b  dd  0xB4B3B2B1
max_uint_c  dd  0xC4C3C2C1
max_uint_d  dd  0xD4D3D2D1
max_uint_e  dd  0xE4E3E2E1
max_uint_f  dd  0xF4F3F2F1
; masks
mask_q_h4   equ 0xFFFFFFFF00000000



