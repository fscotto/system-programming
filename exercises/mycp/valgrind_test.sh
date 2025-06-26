#!/bin/sh

EXEC=./mycp
LOGFILE=valgrind_output.txt
INPUT=test_input.txt
OUTPUT=test_output.txt

echo "Testing with Valgrind..." > "$LOGFILE"
echo "Input: $INPUT → Output: $OUTPUT" >> "$LOGFILE"
echo "----------------------------------------" >> "$LOGFILE"

# Prepara input file
echo "Valgrind test content" > "$INPUT"

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
    "$EXEC" "$INPUT" "$OUTPUT" 2>> "$LOGFILE"

echo "✅ Valgrind test completed. Output in $LOGFILE."

