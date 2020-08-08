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
	gdtr:
	.word 0
	gdtr2:
	.long 0
	stack_bottom:
	.skip 4096
	stack_top:


.section .text
	set_gdt:
	mov %eax, 4(%esp)
	mov (gdtr2), %eax
	mov %ax, 8(%esp)
	mov (gdtr), %ax
	lgdt (gdtr)
	ret

.global load_page_directory
	load_page_directory:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	mov %eax, %cr3
	mov %ebp, %esp
	pop %ebp
	ret

.global enable_paging
	enable_paging:
	push %ebp
	mov %esp, %ebp
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0
	mov %ebp, %esp
	pop %ebp
	ret

	start:
	mov $stack_top, %esp
	call kernel_main

	hang:
	cli
	hlt
	jmp hang
