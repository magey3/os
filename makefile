CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -g -c
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld

src = $(wildcard *.c) $(wildcard *.S)
cobj = $(src:.c=.o)
obj = $(cobj:.S=.o)

%.o: %.S
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

kernel: $(obj)
	$(CC) $(LDFLAGS) $^ -o kernel.elf

.PHONY: clean
clean:
	rm $(obj) kernel.elf
