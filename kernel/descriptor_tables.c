#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables.h"
#include "io/io.h"
#include "interrupt/interrupts.h"

TSS tss;
extern IDT idt[256];
IDTR idtr;

void encodeGdtEntry(uint8_t *target, struct GDT _source)
{
	struct GDT source = _source;
	// Check the limit to make sure that it can be encoded
	if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF)) {
		return;
	}
	if (source.limit > 65536) {
		// Adjust granularity if required
		source.limit = source.limit >> 12;
		target[6] = 0xC0;
	} else {
		target[6] = 0x40;
	}

	// Encode the limit
	target[0] = source.limit & 0xFF;
	target[1] = (source.limit >> 8) & 0xFF;
	target[6] |= (source.limit >> 16) & 0xF;

	// Encode the base 
	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	// And... Type
	target[5] = source.type;
}

void encode_idt_entry(void* int_handler, uint8_t type_attr, uint16_t code_selector, IDT* idt_entry) {
	idt_entry->offset_low = (uint16_t)int_handler & 0xffff;
	idt_entry->selector = code_selector;
	idt_entry->zero = 0;
	idt_entry->type_attr = type_attr;
	idt_entry->offset_high = (uint16_t)((uint32_t)int_handler >> 16) & 0xffff;
}

void init_interrupts(){
	// Remaps the PIC
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
	encode_idt_entry(&irq80, 0x8e, 0x8, &idt[0x80]);
}

void init_descriptor_tables(){
	struct GDT gdt_s[4];
	gdt_s[0].base = 0;
	gdt_s[0].limit = 0;
	gdt_s[0].type = 0;

	gdt_s[1].base = 0;
	gdt_s[1].limit = 0xffffffff;
	gdt_s[1].type = 0x9a;

	gdt_s[2].base = 0;
	gdt_s[2].limit = 0xffffffff;
	gdt_s[2].type = 0x92;

	gdt_s[3].base = (uint32_t)&tss;
	gdt_s[3].limit = 104;
	gdt_s[3].type = 0x89;

	extern uint8_t gdt;
	encodeGdtEntry(&gdt, gdt_s[0]);
	encodeGdtEntry(&gdt+8, gdt_s[1]);
	encodeGdtEntry(&gdt+16, gdt_s[2]);
	encodeGdtEntry(&gdt+24, gdt_s[3]);

	extern void syscall_stack;
	tss.ss0 = 0x10;
	tss.esp0 = &syscall_stack;
	tss.iopb = 104;

	extern void set_gdt(uint32_t gdt, uint16_t size);
	set_gdt((uint32_t)&gdt, 32);
	
	// Load TSS
	extern void set_tss(uint16_t segment);
	set_tss(0x18);
	
	init_interrupts();

	idtr.size = 256*sizeof(IDT)-1;
	idtr.offset = idt;

	extern void load_idt(IDTR* idtr);
	load_idt(&idtr);
}
