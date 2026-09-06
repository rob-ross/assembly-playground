# 1. Assemble to a macOS 64-bit object file
nasm -f macho64 hello.asm -o hello.o

# 2. Link against the system C library using GCC or clang
gcc hello.o -o hello

# 3. Run your program
./hello
