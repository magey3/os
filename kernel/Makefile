CC = i686-elf-gcc
CFLAGS =-I . -std=gnu99 -ffreestanding -g -c -O3
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld

SRC = $(wildcard *.c) $(wildcard *.S)
EXTOBJ = $(wildcard io/*.o) $(wildcard interrupt/*.o)
OBJ = $(patsubst %.c, %.o, $(patsubst %.S, %.o, $(SRC)))

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

kernel: $(OBJ)
	$(MAKE) -C io
	$(MAKE) -C interrupt
	$(CC) $(LDFLAGS) $^ $(EXTOBJ) -o kernel.bin

.PHONY: clean
clean:
	rm $(OBJ) kernel.bin
