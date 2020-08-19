.extern kmain
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

.section .data
.global gdt
	.align 16
.section .bss
	gdt:
	.skip 32
.global idt
	idt:
	.skip 2048
	gdtr:
	.word 0
	.long 0
	stack_bottom:
	.skip 4096
	stack_top:
	syscall_stack_bottom:
	.skip 4096
	.global syscall_stack
	syscall_stack:


.section .text
	set_gdt:
	mov $gdtr, %ebx
	mov 4(%esp), %eax
	mov %eax, 2(%ebx)
	mov 8(%esp), %ax
	mov %ax, (%ebx)
	lgdt (%ebx)

	jmp $0x08, $_flush
	_flush:
	ret
.global set_tss
	set_tss:
	mov 4(%esp), %ax
	ltr %ax
	ret
.global load_idt
	load_idt:
	mov 4(%esp), %eax
	lidt (%eax)
	sti
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

.extern init
	start:
	mov $stack_top, %esp
	call init

	hang:
	cli
	hlt
	jmp hang
