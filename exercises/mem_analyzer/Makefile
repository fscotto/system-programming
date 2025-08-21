CC = gcc
CFLAGS = -Wall -Wextra -Wpadded -g -fsanitize=address
TARGET = mem_analyzer
SRC = mem_utils.c main.c
OBJ = $(SRC:.c=.o)

.PHONY: all build run test valgrind clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(TARGET)

test: build
	./$(TARGET) test

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
