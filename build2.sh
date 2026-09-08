#!/usr/bin/env zsh
set -e # Exit immediately if any command fails

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path/base-name>"
    echo "Example: $0 src/exit"
    echo "Example: $0 src/chapter1/exit"
    exit 1
fi

INPUT_PATH="$1"
ASM_FILE="${INPUT_PATH}.asm"

BASE_NAME="$(basename "$INPUT_PATH")"
BUILD_ROOT="shell-build"
OUTPUT_PATH="${INPUT_PATH#src/}"

BUILD_DIR="${BUILD_ROOT}/${OUTPUT_PATH}"
OBJECT_FILE="${BUILD_DIR}/${BASE_NAME}.o"
LIST_FILE="${BUILD_DIR}/${BASE_NAME}.list"

EXECUTABLE="${BUILD_DIR}/${BASE_NAME}"

if [ ! -f "$ASM_FILE" ]; then
    echo "Error: source file '$ASM_FILE' not found."
    exit 1
fi

mkdir -p "$BUILD_DIR"

# 1. Assemble with debug symbols (-g) to a macOS 64-bit Mach-O object file
nasm -g -f macho64 "$ASM_FILE" -o "$OBJECT_FILE" -l "$LIST_FILE"

# 2. Link using Homebrew Clang, passing -no_pie via -Wl
/usr/local/opt/llvm/bin/clang -Wl,-no_pie "$OBJECT_FILE" -o "$EXECUTABLE"

# 3. Run the compiled executable
echo run $EXECUTABLE ":"
"$EXECUTABLE"
