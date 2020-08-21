#include <stddef.h>
#include <stdint.h>
#include "gdt.h"

gdt_entry_t gdt[3];
gdtr_t gdtr;

gdt_entry_t encode_gdt_entry(uint32_t base, uint32_t limit, uint8_t flags, uint8_t access){
	gdt_entry_t entry;

	entry.limit_low = (uint16_t)(limit & 0xffff);
	entry.base_low = (uint16_t)(base & 0xffff);
	entry.base_mid = (uint8_t)((base >> 16) & 0xff);
	entry.access = access;
	entry.limit_flags = (flags << 4) & 0xf0;
	entry.limit_flags |= (uint8_t)((limit >> 16) & 0xf);
	entry.base_high = (uint8_t)((base >> 24) & 0xff);

	return entry;
}

void setup_gdt(){
	gdt[0] = encode_gdt_entry(0, 0, 0, 0);
	gdt[1] = encode_gdt_entry(0, 0xffffffff, 0b1010, 0b10011010);
	gdt[2] = encode_gdt_entry(0, 0, 0, 0b10010010);

	gdtr.size = 23;
	gdtr.offset = gdt;

	asm volatile("lgdt (%0)" : : "r" (&gdtr));
}
