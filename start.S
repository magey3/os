.extern kernel_main
.global start
.global set_gdt
.global gdt_flush

.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM

.section .bss

	.align 16
	stack_bottom:
	.skip 4096
	stack_top:


.section .text
	gdtr:
	.word 0
	gdtr2:
	.long 0
	set_gdt:
	mov %eax, 4(%esp)
	mov (gdtr2), %eax
	mov %ax, 8(%esp)
	mov (gdtr), %ax
	lgdt (gdtr)
	ret
	start:
	mov $stack_top, %esp
	call kernel_main

	hang:
	cli
	hlt
	jmp hang
