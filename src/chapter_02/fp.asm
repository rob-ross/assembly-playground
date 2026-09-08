; fp.asm
; book command: yasm -f elf64 -g dwarf2 -l fp.lst fp.asm
; nasm -g -f macho64 -l fp.lst fp.asm
segment .data
zero dd 0.0
one dd 1.0
neg1 dd -1.0
a dd 1.75
b dd 122.5
d dd 1.1
e dd 10000000000.0
