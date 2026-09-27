;------------------------------------------------------------------------------
; Ch04_06.asm
;------------------------------------------------------------------------------

default rel

section .text

;------------------------------------------------------------------------------
; void CopyArrayI32_a(int32_t* b, const int32_t* a, size_t n);
;------------------------------------------------------------------------------
global _CopyArrayI32_a
_CopyArrayI32_a:

; Copy a[] to b[]
; (note: rsi and rdi already contain pointers to a[] and b[])
    mov     rcx, rdx    ; rcx := n
    rep     movsd       ; copy elements in rsi[] to rdi[]
    ret

;------------------------------------------------------------------------------
; void FillArrayI64_a(const int64_t* a, int64_t fill_val, size_t n);
;------------------------------------------------------------------------------
global _FillArrayI64_a
_FillArrayI64_a:

; Fill a[] with fill_val
; (note: rdi already contains pointer to a[])
    mov     rax, rsi        ; rax := fill value
    mov     rcx, rdx        ; rcx := n
    rep     stosq           ; set each element in to fill_val. Fills n(rcx) elements
    ret
