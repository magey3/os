CC = i686-elf-gcc
CFLAGS =-I . -std=gnu99 -ffreestanding -g -c -O3
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld

SRC = $(wildcard *.c) $(wildcard *.S)
OBJ = $(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

kernel: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o kernel.bin

.PHONY: clean
clean:
	rm $(OBJ) kernel.bin
