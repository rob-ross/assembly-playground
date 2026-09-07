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


#### System Call Numbers
- Use macOS system call numbers.
- Add 0x2000000 to the book's numbers if writing raw system calls
- E.g., 0x2000004 for `write`, 0x2000001 for `exit`
- or, call the C library functions directly (printf, puts, exit) via `call _printf`.


### Not used

- "end" directive at the end of asm


