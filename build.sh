#!/usr/bin/env zsh
set -e # Exit immediately if any command fails

# 1. Assemble with debug symbols (-g) to a macOS 64-bit Mach-O object file
nasm -g -f macho64 hello.asm -o hello.o

# 2. Link using Homebrew Clang, passing -no_pie via -Wl
/usr/local/opt/llvm/bin/clang -Wl,-no_pie hello.o -o hello

# 3. Run the compiled executable
./hello
