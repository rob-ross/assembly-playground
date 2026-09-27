;------------------------------------------------------------------------------
; Ch04_04.asm
;------------------------------------------------------------------------------

default rel

segment .text
;------------------------------------------------------------------------------
; size_t CountChars_a(const char* s, char c);
;------------------------------------------------------------------------------
global _CountChars_a
_CountChars_a:
; Perform required initializations
    mov      dl, sil    ;  dl := c
    mov     rsi, rdi    ; rsi := s
    xor     ecx, ecx    ; ecx := 0
    xor     r8d, r8d    ; r8 := 0 (required for add to sum)
    nop
; Repeat loop until the entire string has been scanned
; lodsb: load byte at address (R)SI into AL
; after the load, increments/decrements the value in rsi by the size of the operand,
; uses EFLAGS.DF 0 == increment, 1 == decrement. Default on mac/System V is 0
Loop:
    lodsb               ; load next char into register al, increment rsi
    test    al, al      ; test for null-terminator
    jz      Done        ; jump if at end-of-string
    cmp     al, dl      ; test current char against c
    sete    r8b         ; r8b :=1 if equal, 0 if not
    add     rcx, r8     ; num_chars += r8b
    jmp     Loop

; setcc : set destination byte to 1 if condition is met, 0 if not met
; sete : set dest byte to 1 if previous cmp is equal

Done:
    mov rax,rcx                         ; rax = num_chars
    ret
