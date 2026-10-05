#!/bin/sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(dirname "$SCRIPT_DIR")
ARM_BIN=${ARM_TOOLCHAIN_BIN:-/Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.14.3.rel1.macosaarch64_1.0.0.202602081740/tools/bin}
ELF_FILE=${1:-$PROJECT_ROOT/blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf}
OUTPUT_DIR=${2:-$PROJECT_ROOT}

READELF="$ARM_BIN/arm-none-eabi-readelf"
OBJDUMP="$ARM_BIN/arm-none-eabi-objdump"

if [ ! -r "$ELF_FILE" ]; then
    printf 'ELF file not found: %s\n' "$ELF_FILE" >&2
    exit 1
fi

if [ ! -x "$READELF" ] || [ ! -x "$OBJDUMP" ]; then
    printf 'ARM tools not found in: %s\n' "$ARM_BIN" >&2
    printf 'Set ARM_TOOLCHAIN_BIN to the directory containing arm-none-eabi-readelf and arm-none-eabi-objdump.\n' >&2
    exit 1
fi

mkdir -p "$OUTPUT_DIR"

"$READELF" -h -S -l -s "$ELF_FILE" > "$OUTPUT_DIR/elf_report.txt"
"$OBJDUMP" -S "$ELF_FILE" > "$OUTPUT_DIR/disassembly.txt"

printf 'Created:\n  %s\n  %s\n' \
    "$OUTPUT_DIR/elf_report.txt" \
    "$OUTPUT_DIR/disassembly.txt"