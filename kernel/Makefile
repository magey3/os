CC=x86_64-elf-gcc
CFLAGS=-mno-red-zone -I . -std=gnu99 -ffreestanding -g -c -O3
LDFLAGS=-n -ffreestanding -nostdlib -g -T linker.ld

SRC= $(wildcard *.c) $(wildcard *.S)
EXTOBJ=$(wildcard interrupts/*.o) $(wildcard io/*.o) $(wildcard io/vga/*.o)
OBJ=$(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

kernel: $(OBJ)
	$(MAKE) -C io
	$(MAKE) -C interrupts
	$(CC) $(LDFLAGS) $^ $(EXTOBJ) -o kernel.bin

.PHONY: clean
clean:
	$(MAKE) -C io clean
	$(MAKE) -C interrupts clean
	rm $(OBJ) kernel.bin
