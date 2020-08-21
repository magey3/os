.set MB_CHECKSUM, 0x100000000-(0xe85250d6 + 0 + 24)
.section .multiboot
	.align 8
	.int 0xe85250d6
	.int 0
	.int 24
	.int MB_CHECKSUM
	.word 0
	.word 0
	.int 8
