### Number types

- hex:     0x20 or 20h
- base 10: 20
- base 2 : 1011b or 1011y
- base 8 : 777o or 777q

### Mac OS

- entry point is "_main"
- no_pie </p>
  PIE stands for Position-Independent Executable. It's a security feature where the memory addresses 
   are different each time. -no_pie allows for using absolute addresses.
<p>

#### To use relative address in asm files:
- Remove -no_pie from build scripts.
- Use lea for string/data pointers (e.g., lea rsi, [message]) rather than mov rsi, message.
<p>
In 64-bit x86 assembly, the CPU calculates memory locations relative to its current instruction pointer (RIP).
Whenever a code example in the book accesses a variable in section .data or section .bss:

Book's Style (Absolute Address):
```c
mov rsi, message     ; Moves absolute memory address of message into rsi
mov rax, [my_var]    ; Loads memory value at absolute address my_var
```
Modern macOS / PIE Style (Relative Address):
```d
lea rsi, [rel message]   ; Load Effective Address relative to instruction pointer
mov rax, [rel my_var]    ; Load value relative to instruction pointer
```
</p>

- add "default rel" at the top of each asm file so you don't have to add `rel` in each command
- System Call Convention: macOS System V ABI prefers using the full 64-bit rdi register for system call arguments.


#### System Call Numbers
- Use macOS system call numbers.
- Add 0x2000000 to the book's numbers if writing raw system calls
- E.g., 0x2000004 for `write`, 0x2000001 for `exit`
- or, call the C library functions directly (printf, puts, exit) via `call _printf`.


### Not used

- "end" directive at the end of asm

---

## Registers
| Register Name | Size      | Description              |                                               |
|---------------|-----------|--------------------------|-----------------------------------------------|
| rdi, 64 bits  | (8 bytes) | The full 64-bit register | used as first arg to function or system call  |
| edi, 32 bits  | (4 bytes) | The lower 32 bits of rdi | used as first arg to function or system call  |
| di,  16 bits  | (2 bytes) | The lower 16 bits of edi |                                               |
| dil,  8 bits  | (1 byte)  | The lower 8 bits of di   |                                               |

---
In original 16-bit x86 assembly, registers had specific hardware roles:
- si (Source Index): Pointed to the memory location you were reading from.
- di (Destination Index): Pointed to the memory location you were writing to.

They were primarily designed for string/memory manipulation instructions like movsb (Move String Byte) or 
stosb (Store String Byte), where rsi/ds:si served as the source pointer and rdi/es:di served as the destination pointer.
---
| Register | Full Name                                | Architecture    | Size      | Era  |
|----------|------------------------------------------|-----------------|-----------|------|
| di       | Destination Index                        | 16-bit (8086)   | 16 bits   | 1978 |
| edi      | Extended Destination Index               | 32-bit (80386)  | 32 bits   | 1985 |
| rdi      | Register (or 64-bit) Destination Index   | 64-bit (x86-64) | 64 bits   | 2003 |

### Debugging
- in lldb enter `regist read` to see general purpose registers
- or enter specific registers, e.g., register read rax rbx rcx rdx rbp rsp rip
