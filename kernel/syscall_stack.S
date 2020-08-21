.section .bss
	_syscall_stack_bottom:
	.skip 4096
	.global _syscall_stack
	_syscall_stack:
