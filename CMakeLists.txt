
cmake_minimum_required(VERSION 3.20)
#cmake_minimum_required(VERSION 4.3.1)

project(assembly_playground C CXX ASM_NASM)
set(CMAKE_CXX_STANDARD 23)

# Ensure CMake uses 64-bit NASM for macOS Mach-O binaries
set(CMAKE_ASM_NASM_OBJECT_FORMAT macho64)

# Set global flags for NASM debug symbols
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -g -F dwarf")


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

add_executable(ch02_01
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01.cpp
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01_misc.cpp
        modern-x86-assembly/ch_02/ch_02_01/Ch02_01_fasm.asm
)
set_target_properties(ch02_01 PROPERTIES LINKER_LANGUAGE CXX)

# chapter 2
# ----------
add_executable(ch02_02
        modern-x86-assembly/ch_02/Ch02_02.cpp
        modern-x86-assembly/ch_02/Ch02_02.asm
)
set_target_properties(ch02_02 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch02_03
        modern-x86-assembly/ch_02/Ch02_03.cpp
        modern-x86-assembly/ch_02/Ch02_03.asm
)
set_target_properties(ch02_03 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch02_04
        modern-x86-assembly/ch_02/Ch02_04.cpp
        modern-x86-assembly/ch_02/Ch02_04.asm
)
set_target_properties(ch02_04 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch02_05
        modern-x86-assembly/ch_02/Ch02_05.cpp
        modern-x86-assembly/ch_02/Ch02_05.asm
)
set_target_properties(ch02_05 PROPERTIES LINKER_LANGUAGE CXX)

# chapter 3
# ----------
add_executable(ch03_01
        modern-x86-assembly/ch_03/Ch03_01.cpp
        modern-x86-assembly/ch_03/Ch03_01.asm
)
set_target_properties(ch03_01 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch03_02
        modern-x86-assembly/ch_03/Ch03_02.cpp
        modern-x86-assembly/ch_03/Ch03_02.asm
)
set_target_properties(ch03_02 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch03_03
        modern-x86-assembly/ch_03/Ch03_03.cpp
        modern-x86-assembly/ch_03/Ch03_03.asm
)
set_target_properties(ch03_03 PROPERTIES LINKER_LANGUAGE CXX)

#project(ch03_04 CXX ASM_NASM)
add_executable(ch03_04
        modern-x86-assembly/ch_03/Ch03_04.cpp
        modern-x86-assembly/ch_03/Ch03_04.asm
)
set_target_properties(ch03_04 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch03_05
        modern-x86-assembly/ch_03/Ch03_05.cpp
        modern-x86-assembly/ch_03/Ch03_05.asm
)
set_target_properties(ch03_05 PROPERTIES LINKER_LANGUAGE CXX)

# chapter 4
# ---------
add_executable(ch04_01
        modern-x86-assembly/ch_04/Ch04_01.cpp
        modern-x86-assembly/ch_04/Ch04_01.asm
)
set_target_properties(ch04_01 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_02
        modern-x86-assembly/ch_04/Ch04_02.cpp
        modern-x86-assembly/ch_04/Ch04_02.asm
)
set_target_properties(ch04_02 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_03
        modern-x86-assembly/ch_04/Ch04_03.cpp
        modern-x86-assembly/ch_04/Ch04_03.asm
)
set_target_properties(ch04_03 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_04
        modern-x86-assembly/ch_04/Ch04_04.cpp
        modern-x86-assembly/ch_04/Ch04_04.asm
)
set_target_properties(ch04_04 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_05
        modern-x86-assembly/ch_04/Ch04_05.cpp
        modern-x86-assembly/ch_04/Ch04_05.asm
)
set_target_properties(ch04_05 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_06
        modern-x86-assembly/ch_04/Ch04_06.cpp
        modern-x86-assembly/ch_04/Ch04_06.asm
)
set_target_properties(ch04_06 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_07
        modern-x86-assembly/ch_04/Ch04_07.cpp
        modern-x86-assembly/ch_04/Ch04_07.asm
)
set_target_properties(ch04_07 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch04_08
        modern-x86-assembly/ch_04/Ch04_08.cpp
        modern-x86-assembly/ch_04/Ch04_08.asm
)
set_target_properties(ch04_08 PROPERTIES LINKER_LANGUAGE CXX)

# chapter 5
# ----------
add_executable(ch05_01
        modern-x86-assembly/ch_05/Ch05_01.cpp
        modern-x86-assembly/ch_05/Ch05_01.asm
)
set_target_properties(ch05_01 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_02
        modern-x86-assembly/ch_05/Ch05_02.cpp
        modern-x86-assembly/ch_05/Ch05_02.asm
)
set_target_properties(ch05_02 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_03
        modern-x86-assembly/ch_05/Ch05_03.cpp
        modern-x86-assembly/ch_05/Ch05_03.asm
)
set_target_properties(ch05_03 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_04
        modern-x86-assembly/ch_05/Ch05_04.cpp
        modern-x86-assembly/ch_05/Ch05_04.asm
)
set_target_properties(ch05_04 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_05
        modern-x86-assembly/ch_05/Ch05_05.cpp
        modern-x86-assembly/ch_05/Ch05_05.nasm
        modern-x86-assembly/ch_05/cmpequ_fp.nasmh
)
target_include_directories(ch05_05 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/modern-x86-assembly/ch_05"
)
set_target_properties(ch05_05 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_06
        modern-x86-assembly/ch_05/Ch05_06.cpp
        modern-x86-assembly/ch_05/Ch05_06.asm
)
set_target_properties(ch05_06 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ch05_07
        modern-x86-assembly/ch_05/Ch05_07.cpp
        modern-x86-assembly/ch_05/Ch05_07.asm
)
target_include_directories(ch05_07 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/modern-x86-assembly/ch_05"
)
set_target_properties(ch05_07 PROPERTIES LINKER_LANGUAGE CXX)
