#!/bin/bash

TREE_EXEC="../tree"
TEST_DIR="testdir"
REF_OUTPUT="expected_output.txt"
OUT_FILE="actual_output.txt"
VALGRIND_LOG="valgrind.log"

# Preparazione struttura di test
setup() {
    rm -rf "$TEST_DIR"
    mkdir -p "$TEST_DIR/sub1"
    mkdir -p "$TEST_DIR/sub2"
    touch "$TEST_DIR/file1.txt"
    touch "$TEST_DIR/sub1/file2.txt"
    touch "$TEST_DIR/sub2/file3.txt"

    cat > "$REF_OUTPUT" <<EOF
|-- file1.txt
|-- sub1
  |-- file2.txt
|-- sub2
  |-- file3.txt
EOF
}

# Esecuzione tree e confronto output
run_test() {
    echo "[*] Running functional test..."
    "$TREE_EXEC" "$TEST_DIR" | grep -v "^\\." > "$OUT_FILE"

    if diff -q "$OUT_FILE" "$REF_OUTPUT"; then
        echo "[✓] Output matches expected output."
    else
        echo "[✗] Output differs!"
        diff "$OUT_FILE" "$REF_OUTPUT"
        return 1
    fi
}

# Valgrind check
run_valgrind() {
    echo "[*] Running Valgrind..."
    valgrind --leak-check=full --log-file="$VALGRIND_LOG" "$TREE_EXEC" "$TEST_DIR" > /dev/null

    if grep -q "no leaks are possible" "$VALGRIND_LOG"; then
        echo "[✓] Valgrind: No memory leaks."
    else
        echo "[✗] Valgrind detected memory issues:"
        cat "$VALGRIND_LOG"
        return 1
    fi
}

cleanup() {
    rm -rf "$TEST_DIR" "$OUT_FILE" "$VALGRIND_LOG" "$REF_OUTPUT"
}

main() {
    setup
    run_test || exit 1
    run_valgrind || exit 1
    cleanup
    echo "[✓] All tests passed."
}

main

