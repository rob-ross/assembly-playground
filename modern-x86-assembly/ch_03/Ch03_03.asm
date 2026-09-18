;------------------------------------------------------------------------------
; Ch03_03.asm
;------------------------------------------------------------------------------

default rel  ; use RIP-relative addressing for variable addresses instead of ABS (absolute)


; Simple LUT (section .rdata is read only)
section .rodata

; first 25 primes
PrimeNums:      dd 2, 3, 5, 7, 11, 13, 17, 19, 23
                dd 29, 31, 37, 41, 43, 47, 53, 59
                dd 61, 67, 71, 73, 79, 83, 89, 97

global _g_NumPrimes_a
; remember, _g_NumPrimes_a is memory address at which the value is stored.
_g_NumPrimes_a:  dd ($ - PrimeNums) / 4


; Data section (section .data is read/write)
segment .data

global _g_SumPrimes_a
_g_SumPrimes_a: dd -9999

segment .text

global _MemAddressing_a
;   int MemAddressing_a(
;        int32_t   i,   -> edi
;        int32_t* v1,   -> rsi  pointer
;        int32_t* v2,   -> rdx  pointer
;        int32_t* v3,   -> rcx  pointer
;        int32_t* v4    -> r8   pointer
;   );

align 16
_MemAddressing_a:

; Make sure 'i' is valid
    cmp edi, -1         ; if i <= -1
    jle InvalidIndex    ;   goto InvalidIndex
; In NASM, rel forces RIP-relative addressing for that memory operand
; the address is computed as RIP + offset_to_g_NumPrimes_a. And the value at thi address is then
; compared to the value in edi
    cmp edi, [ rel _g_NumPrimes_a ]
    jge  InvalidIndex    ; jump if i >= _g_NumPrimes_a

; Initialize
    movsxd  r10, edi                ; save the sign-extended value of i to r10 as it will be reused several times
    lea     r11, [ rel PrimeNums]   ; address of LUT is stored in r11
;    lea     r11, PrimeNums         ; NASM convenience form, prefer the bracket form
;    mov     r11,  PrimeNums        ; does not work with a PIE, as this requires text-relocation for the address

; Memory addressing - base register
    mov     rdi, r10                ; rdi := i
    shl     rdi, 2                  ; rdi *= 4  ; we multiply by 4 since each element in LUT is a 4-byte int
    mov     rax, r11                ; rax := PrimeNums (rax has address of LUT table)
    add     rax, rdi                ; rax := PrimeNums + ( i * 4)
    mov     eax, [rax]              ; eax := PrimeNums[i * 4]
    mov     [rsi], eax              ; save to v1

; Memory addressing - base register + index register
    mov     rdi, r10                ; rdi := i
    shl     rdi, 2                  ; rdi := i * 4
    mov     eax, [ r11 + rdi ]      ; eax := PrimeNums[i]
    mov     [rdx], eax              ; save to v2

; Memory addressing - base register + index register * scale factor
    mov     eax, [r11+r10*4]        ; eax := PrimeNums[i]
    mov     [rcx], eax              ; save to v3

; Memory addressing - base register + index register * scale factor + disp
    sub     r11, 42                 ; r11 := r11 - 42 ; PrimeNums - 42
    mov     eax, [r11+r10*4+42]     ; eax := PrimeNums[i]
    mov     [r8],  eax              ; save to v4

; Memory addressing - RIP relative
    add     [_g_SumPrimes_a], eax    ; update sum
    mov     eax,1                    ; set success return code
    ret

InvalidIndex:
    xor eax,eax     ; set error return code
    ret
