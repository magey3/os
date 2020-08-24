#include <stddef.h>
#include <stdint.h>
#include "idt.h"
#include "interrupts/interrupts.h"

idt_entry_t idt[256];
idtr_t idtr;

void encode_idt_entry(idt_entry_t* entry, void* offset, uint16_t selector, uint8_t ist, uint8_t type) {
	entry->offset_low = (uint16_t)((uint64_t)offset & 0xffff);
	entry->offset_mid = (uint16_t)(((uint64_t)offset >> 16) & 0xffff);
	entry->offset_high = (uint32_t)(((uint64_t)offset >> 32) & 0xffffffff);
	entry->ist = ist;
	entry->cs = selector;
	entry->type_attr = type;
	entry->zero = 0;
}

void setup_idt(){
	idtr.size = sizeof(idt_entry_t)*256;
	idtr.offset = idt;

	remap_pic();
	
	encode_idt_entry(&idt[0x80], irq128, 0x8, 0, 0x8f);

	asm volatile("lidt (%0)" : : "r" (&idtr));
}
