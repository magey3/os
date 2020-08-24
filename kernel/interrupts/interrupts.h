#ifndef INTERRUPTS_H
#define INTERRUPTS_H

typedef struct {
	uint16_t ss;
	uint64_t rsp;
	uint64_t rflags;
	uint16_t cs;
	uint64_t rip;
} __attribute__((packed)) int_stack_frame_t;

void remap_pic();

__attribute__((interrupt)) void irq128(int_stack_frame_t* frame);

#endif
