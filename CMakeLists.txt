
cmake_minimum_required(VERSION 3.20)
#cmake_minimum_required(VERSION 4.3.1)

project(assembly_playground C ASM_NASM)

# Ensure CMake uses 64-bit NASM for macOS Mach-O binaries
set(CMAKE_ASM_NASM_OBJECT_FORMAT macho64)

# Set global flags for NASM (e.g., enable dwarf debug symbols)
set(CMAKE_ASM_NASM_FLAGS "-g -f macho64")

# Add your assembly source file(s)
add_executable(assembly_playground
        src/hello.asm
)

# Fix for macOS modern linker warnings regarding command-line entry points
# PIE stands for Position-Independent Executable.
# RIP - (register?) current Instruction Pointer
target_link_options(assembly_playground PRIVATE -no_pie)
