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
	$(CC) $(LDFLAGS) $^ -o kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin ./isodir/boot/kernel.bin
	cp grub.cfg ./isodir/boot/grub/grub.cfg
	rm -f os.iso
	grub-mkrescue -o os.iso isodir

.PHONY: clean
clean:
	rm $(obj) kernel.bin os.iso
	rm -r isodir
