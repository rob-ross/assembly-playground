
cmake_minimum_required(VERSION 3.20)
#cmake_minimum_required(VERSION 4.3.1)

project(assembly_playground C CXX ASM_NASM)
set(CMAKE_CXX_STANDARD 23)

# Ensure CMake uses 64-bit NASM for macOS Mach-O binaries
set(CMAKE_ASM_NASM_OBJECT_FORMAT macho64)

# Set global flags for NASM debug symbols
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -g -F dwarf")


# Define external roblib dependency
add_library(roblib STATIC IMPORTED)
# ${CMAKE_CURRENT_SOURCE_DIR} is the top-level project directory.
set_target_properties(roblib PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libc_roblib.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/external/include"
        # Since libc_roblib.a was built with sanitizers, anyone linking against it
        # MUST also use those sanitizer flags to pull in the required runtimes.
        # Only pass sanitize flags to C and C++ compilers, not to NASM
        INTERFACE_COMPILE_OPTIONS "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C,CXX>>:-fsanitize=address;-fsanitize=leak>"
        INTERFACE_LINK_OPTIONS "$<$<CONFIG:Debug>:-fsanitize=address;-fsanitize=leak>"
)


# Add your assembly source file(s)
add_executable(assembly_playground
        src/unaligned_call_test.asm
#        src/hello.asm
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


function(add_asm_example target_name)
    add_executable(${target_name} ${ARGN})
    set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${target_name} PRIVATE roblib)
endfunction()

function(add_asm_chapter_range chapter_num start_idx end_idx)
    # Ensure chapter has a 2-digit zero-padded string (e.g., 2 -> "02")
    if(chapter_num LESS 10)
        set(ch_pad "0${chapter_num}")
    else()
        set(ch_pad "${chapter_num}")
    endif()

    foreach(i RANGE ${start_idx} ${end_idx})
        # Ensure example index has a 2-digit zero-padded string (e.g., 1 -> "01")
        if(i LESS 10)
            set(idx_pad "0${i}")
        else()
            set(idx_pad "${i}")
        endif()

        set(target_name "ch${ch_pad}_${idx_pad}")
        set(base_path "modern-x86-assembly/ch_${ch_pad}/Ch${ch_pad}_${idx_pad}")

        add_asm_example(${target_name}
                "${base_path}.cpp"
                "${base_path}.asm"
        )
    endforeach()
endfunction()


# example of custom call to add_asm_example
#add_asm_example(ch02_01
#        modern-x86-assembly/ch_02/Ch02_01.cpp
#        modern-x86-assembly/ch_02/Ch02_01.asm
#)

add_asm_chapter_range(2 1 5) # Generates ch02_01 through ch02_05
add_asm_chapter_range(3 1 5)  # Generates ch03_01 through ch03_05
add_asm_chapter_range(4 1 8)  # Generates ch04_01 through ch04_08

# chapter 5
# ----------
add_asm_chapter_range(5 1 4)  # Generates ch05_01 through ch05_04

add_executable(ch05_05
        modern-x86-assembly/ch_05/Ch05_05.cpp
        # these were named with `.nasm` extension to experiment with a different file type in the CLion editor
        modern-x86-assembly/ch_05/Ch05_05.nasm
        modern-x86-assembly/ch_05/cmpequ_fp.nasmh
)
target_include_directories(ch05_05 PRIVATE
        # this is required so that Ch05_05.nasm can include "cmpequ_fp.nasmh"
        "${CMAKE_CURRENT_SOURCE_DIR}/modern-x86-assembly/ch_05"
)
set_target_properties(ch05_05 PROPERTIES LINKER_LANGUAGE CXX)

add_asm_chapter_range(5 6 7)  # Generates ch05_06 through ch05_07
# ----------

add_asm_chapter_range(6 5 7)  # Generates ch06_05 through ch06_07
add_asm_chapter_range(7 1 1)  # Generates ch07_01 through ch07_01
add_asm_chapter_range(8 1 6)  # Generates ch08_01 through ch08_06
add_asm_chapter_range(9 1 1)  # Generates ch08_01 through ch09_


