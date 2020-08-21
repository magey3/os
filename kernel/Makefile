CC=x86_64-elf-gcc
CFLAGS=-mno-red-zone -mno-mmx -mno-sse -mno-sse2 -I . -std=gnu99 -ffreestanding -g -c -O3
LDFLAGS=-n -ffreestanding -nostdlib -g -T linker.ld

SRC= $(wildcard *.c) $(wildcard *.S)
EXTOBJ=
OBJ=$(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

kernel: $(OBJ)
	$(CC) $(LDFLAGS) $^ $(EXTOBJ) -o kernel.bin

.PHONY: clean
clean:
	rm $(OBJ) kernel.bin
