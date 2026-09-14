
cmake_minimum_required(VERSION 3.20)
#cmake_minimum_required(VERSION 4.3.1)

project(assembly_playground C ASM_NASM)

# Ensure CMake uses 64-bit NASM for macOS Mach-O binaries
set(CMAKE_ASM_NASM_OBJECT_FORMAT macho64)

# Set global flags for NASM (e.g., enable dwarf debug symbols)
set(CMAKE_ASM_NASM_FLAGS "-g -F dwarf -f macho64")

# Add your assembly source file(s)
add_executable(assembly_playground
        src/hello.asm
        #src/chapter_03/memory.asm
        #src/hello3.asm
#        src/nibblebits/test_print.asm
#        src/test_registers.asm
)

set_target_properties(assembly_playground PROPERTIES LINKER_LANGUAGE C)


# Fix for macOS modern linker warnings regarding command-line entry points
# PIE stands for Position-Independent Executable.
# RIP - (register?) current Instruction Pointer
#target_link_options(assembly_playground PRIVATE -no_pie)


######################################################
#
# X86-64 Core Programming 3rd Edition projects:
#
######################################################

project(ch02_01 CXX ASM_NASM)
add_executable(ch02_01
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01.cpp
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01_misc.cpp
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01_fasm.asm
)
set_target_properties(ch02_01 PROPERTIES LINKER_LANGUAGE CXX)

project(ch02_02 CXX ASM_NASM)
add_executable(ch02_02
        modern-x86-assembly/ch_02/Ch02_02.cpp
        modern-x86-assembly/ch_02/Ch02_02.asm
)
set_target_properties(ch02_02 PROPERTIES LINKER_LANGUAGE CXX)

project(ch02_03 CXX ASM_NASM)
add_executable(ch02_03
        modern-x86-assembly/ch_02/Ch02_03.cpp
        modern-x86-assembly/ch_02/Ch02_03.asm
)
set_target_properties(ch02_03 PROPERTIES LINKER_LANGUAGE CXX)

project(ch02_04 CXX ASM_NASM)
add_executable(ch02_04
        modern-x86-assembly/ch_02/Ch02_04.cpp
        modern-x86-assembly/ch_02/Ch02_04.asm
)
set_target_properties(ch02_04 PROPERTIES LINKER_LANGUAGE CXX)

project(ch02_05 CXX ASM_NASM)
add_executable(ch02_05
        modern-x86-assembly/ch_02/Ch02_05.cpp
        modern-x86-assembly/ch_02/Ch02_05.asm
)
set_target_properties(ch02_05 PROPERTIES LINKER_LANGUAGE CXX)
