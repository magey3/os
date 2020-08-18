#ifndef INTERRUPTS_H
#define INTERRUPTS_H

typedef struct {
	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t sp;
	uint32_t ss;
} __attribute__((packed)) stack_frame;

__attribute__((interrupt)) void irq80(stack_frame* frame);

#endif
