CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC = main.c tree.c
OBJ = $(SRC:.c=.o)
EXEC = tree

# Main target
all: $(EXEC)

# Build executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Run test suite
test: all
	@cd test && ./run_tests.sh

# Clean object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Full cleanup (also test artifacts)
distclean: clean
	cd test && rm -f actual_output.txt valgrind.log expected_output.txt && rm -rf testdir

.PHONY: all test clean distclean

