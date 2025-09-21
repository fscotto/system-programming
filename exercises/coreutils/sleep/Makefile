CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c11 -pthread -g
TARGET  := sleep
SRC     := main.c
OBJS    := $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

