.section .text
.code32
.global start
	start:
	mov $stack_top, %esp

	// Check bootloader magic number
	mov %ebx, mb_info
	cmp $0x36d76289, %eax
	jne _hlt
	
	//Enable SSE
	mov %cr0, %eax
	and $0xfffb, %ax
	or $0x2, %ax
	mov %eax, %cr0
	mov %cr4, %eax
	or 3<<9, %ax
	mov %eax, %cr4

	// Prepare page table
	mov $0x1000, %edi // PROBABLY NOT A GOOD IDEA BUT EVERYTHING ELSE DOESNT WORK
	mov %edi, %cr3
	xor %eax, %eax
	mov $4096, %ecx
	rep stosl
	mov %cr3, %edi
	
	movl $0x2003, (%edi)
	add $0x1000, %edi

	movl $0x3003, (%edi)
	add $0x1000, %edi

	movl $0x4003, (%edi)
	add $0x1000, %edi

	mov $0x00000003, %ebx
	mov $512, %ecx

	_set_entry:
	movl %ebx, (%edi)
	add $0x1000, %ebx
	add $8, %edi
	loop _set_entry

	mov %cr4, %eax
	or $(1<<5), %eax
	mov %eax, %cr4

	// Set LM bit
	mov $0xC0000080, %ecx
	rdmsr
	or $(1<<8), %eax
	wrmsr

	// Enable paging
	mov %cr0, %eax
	or $(1<<31), %eax
	mov %eax, %cr0

	// Load GDT
	lgdt (gdtr)
	jmp $0x08, $_exit

	_exit:
.code64
.extern kmain
	call kmain

	_hlt:
	cli
	hlt
	jmp _hlt

.section .data
	gdt_null:
	.word 0xffff
	.word 0
	.byte 0
	.byte 0
	.byte 1
	.byte 0
	gdt_code:
	.word 0
	.word 0
	.byte 0
	.byte 0b10011010
	.byte 0b10101111
	.byte 0
	gdt_data:
	.word 0
	.word 0
	.byte 0
	.byte 0b10010010
	.byte 0
	.byte 0
	gdtr:
	.word 24
	.quad gdt_null

.section .bss
.align 16
	stack_bottom:
	.skip 8192
	stack_top:
	mb_info:
	.skip 4
	.align 4096
	pml4t:
	.skip 4096
	pdpt:
	.skip 4096
	pdt:
	.skip 4096
	pt:
	.skip 4096
