CC=x86_64-elf-gcc
CFLAGS=-mno-red-zone -I .. -std=gnu99 -ffreestanding -g -c -O3 -mgeneral-regs-only
LDFLAGS=-n -ffreestanding -nostdlib -g -T linker.ld

SRC= $(wildcard *.c) $(wildcard *.S)
OBJ=$(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

obj: $(OBJ)
	$(MAKE) -C vga

.PHONY: clean
clean:
	$(MAKE) -C vga clean
	rm $(OBJ)
