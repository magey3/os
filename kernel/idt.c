#include <stddef.h>
#include <stdint.h>
#include "idt.h"

idt_entry_t idt[256];
idtr_t idtr;

idt_entry_t encode_idt_entry(void* offset, uint16_t selector, uint8_t ist, uint8_t type) {
	idt_entry_t entry;
	entry.offset_low = (uint16_t)((uint64_t)offset & 0xffff);
	entry.offset_mid = (uint16_t)(((uint64_t)offset >> 16) & 0xffff);
	entry.offset_high = (uint32_t)(((uint64_t)offset >> 32) & 0xffffffff);
	entry.ist = ist;
	entry.type_attr = type;
	entry.zero = 0;

	return entry;
}

void setup_idt(){
	idtr.size = sizeof(idt_entry_t)*256;
	idtr.offset = idt;

	asm volatile("lidt (%0)" : : "r" (&idtr));
}
