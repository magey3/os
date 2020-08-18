CC = i686-elf-gcc
CFLAGS =-I .. -std=gnu99 -ffreestanding -g -c -O3 -mgeneral-regs-only

SRC = $(wildcard *.c) $(wildcard *.S)
OBJ = $(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

all: $(OBJ)

.PHONY: clean
clean:
	rm $(OBJ)
