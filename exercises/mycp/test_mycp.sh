#!/bin/sh

EXEC=./mycp
LOGFILE=test_results.log
PASS=0
FAIL=0

echo "[INFO] Running tests for $EXEC" > "$LOGFILE"
echo "[INFO] Date: $(date)" >> "$LOGFILE"
echo "===================================" >> "$LOGFILE"

log() {
    echo "$1" | tee -a "$LOGFILE"
}

check() {
    DESC="$1"
    CMD="$2"
    EXPECT="$3"

    log "[TEST] $DESC"
    eval "$CMD" > /dev/null 2>&1
    RET=$?

    if [ "$RET" -eq "$EXPECT" ]; then
        log "  ✔ SUCCESS (exit code $RET)"
        PASS=$((PASS + 1))
    else
        log "  ✘ FAIL (exit code $RET, expected $EXPECT)"
        FAIL=$((FAIL + 1))
    fi
}

compare_files() {
    FILE1="$1"
    FILE2="$2"
    if cmp -s "$FILE1" "$FILE2"; then
        log "  ✔ Files are identical"
    else
        log "  ✘ Files differ!"
        FAIL=$((FAIL + 1))
    fi
}

# Test 1
echo "Hello World" > test_input.txt
check "Copy text file" "$EXEC test_input.txt test_output.txt" 0
compare_files test_input.txt test_output.txt

# Test 2
cp /bin/ls bin_input
check "Copy binary file" "$EXEC bin_input bin_output" 0
compare_files bin_input bin_output

# Test 3
check "Source file does not exist" "$EXEC nofile.txt shouldnotexist" 1

# Test 4
check "Missing arguments" "$EXEC" 1

# Test 5
echo "readonly" > readonly.txt
chmod 444 readonly.txt
check "Write to read-only file" "$EXEC test_input.txt readonly.txt" 1
chmod 644 readonly.txt

# Test 6
echo "old content" > existing.txt
check "Overwrite existing file" "$EXEC test_input.txt existing.txt" 0
compare_files test_input.txt existing.txt

# Test 7
dd if=/dev/urandom of=bigfile bs=1K count=128 status=none
check "Copy large file (128KB)" "$EXEC bigfile bigfile_copy" 0
compare_files bigfile bigfile_copy

# Summary
log ""
log "Tests passed: $PASS"
log "Tests failed: $FAIL"

if [ "$FAIL" -eq 0 ]; then
    log "✅ All tests passed"
    exit 0
else
    log "❌ Some tests failed"
    exit 1
fi

