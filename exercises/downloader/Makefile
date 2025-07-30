# Makefile for Multi-threaded File Downloader

CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c11 -pthread -g
TARGET  := downloader
SRC     := main.c
OBJS    := $(SRC:.c=.o)

.PHONY: all clean test valgrind

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./downloader test1.txt test2.txt test3.txt

valgrind: $(TARGET)
	valgrind --leak-check=full ./downloader test1.txt test2.txt

clean:
	rm -f $(TARGET) $(OBJS)

