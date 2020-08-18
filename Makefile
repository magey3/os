all:
	$(MAKE) -C ./kernel
	rm -f os.iso
	cp kernel/kernel.bin isodir/boot
	grub-mkrescue -o os.iso isodir

.PHONY: clean
clean:
	$(MAKE) -C kernel clean
	rm -f os.iso
