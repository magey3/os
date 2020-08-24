#include <stddef.h>
#include <stdint.h>
#include "interrupts/interrupts.h"
#include "io/io.h"
#include "io/vga/mtxt_print.h"

void remap_pic() {
	/* remapping the PIC */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 40);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

__attribute__((interrupt)) void irq128(int_stack_frame_t* frame) {
	print("INTERRUPT 0x80");
	outb(0x20, 0x20);
}
