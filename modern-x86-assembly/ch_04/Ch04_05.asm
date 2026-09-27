;------------------------------------------------------------------------------
; Ch04_05.asm
;------------------------------------------------------------------------------

default rel

section .text

;------------------------------------------------------------------------------
;                                      edi,              esi,      rdx
; int64_t CompareArrays_a(const int32_t* x, const int32_t* y, int64_t n);
;
; Returns       -1          Value of n is invalid
;               0 <= i < n  Index of first non-matching element
;               n           All elements match
;------------------------------------------------------------------------------
global _CompareArrays_a
_CompareArrays_a:
; Validate n
    mov     rax, -1     ; rax := -1
    test    rdx, rdx    ;
    jle     Done        ; jump if n <= 0

; Compare the arrays for equality
; (rsi and rdi already contain pointers to arrays x and y)
    mov     rcx, rdx    ; save n, rcx := n
    mov     rax, rdx    ; rax := n
; repe : repeat wile equal. compares array values from rdi, rsi. then increments both by 4 (d == double word)
; it also subtracts 1 from rcx. It continues until rcx is 0 or the elements do not equal each other
    repe cmpsd           ; compare arrays

; Calculate index of first non-match
    jz      Done        ; jump if arrays are equal
    sub     rax, rcx    ; rax := index of mismatch + 1
    sub     rax, 1      ; rax := index of mismatch

; Calculate index of first non-match

Done:
    ret
