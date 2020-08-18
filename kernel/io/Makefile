CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O3 -Wall -Wextra -I ..

SRC=$(wildcard *.c) $(wildcard *.s)
OBJ=$(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SRC)))

.PHONY: clean

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)

clean:
	rm $(OBJ)
