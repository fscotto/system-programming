# Nome del file eseguibile
TARGET = mycp

# Compilatore
CC = gcc

# Opzioni di compilazione (C11 + warning utili + debug info)
CFLAGS = -Wall -Wextra -fsanitize=address -lasan -std=c11 -g

# File sorgente
SRC = main.c

LOGFILE = test_results.log

HTMLREPORT = test_report.html

VALGRIND_OUTPUT = valgrind_output.txt

.PHONY: all clean clean-tests test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: clean-tests $(TARGET)
	./test_mycp.sh

clean-tests:
	@echo "[CLEANUP] Removing test files and logs..."
	rm -f \
	    test_input.txt \
	    test_output.txt \
	    bin_input \
	    bin_output \
	    readonly.txt \
	    existing.txt \
	    bigfile \
	    bigfile_copy \
	    *.copy \
	    $(LOGFILE) \
	    $(HTMLREPORT) \
        $(VALGRIND_OUTPUT)

clean: clean-tests
	rm -f $(TARGET)

report: test
	./generate_report.sh

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./mycp test_input.txt test_output.txt

valgrind-test: $(TARGET)
	./valgrind_test.sh

