# Makefile for sequential script executor project

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = run_scripts
SRC = main.c

.PHONY: all clean run test valgrind

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET) tests/hello.sh tests/fail.sh

test: run

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) scripts/test1.sh scripts/test2.sh

clean:
	rm -f $(TARGET)
