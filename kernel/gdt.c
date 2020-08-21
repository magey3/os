#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "tss.h"

gdt_t gdt;
gdtr_t gdtr;
tss_t tss;

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
	gdt.null = encode_gdt_entry(0, 0, 0, 0);
	gdt.code = encode_gdt_entry(0, 0xffffffff, 0b1010, 0b10011010);
	gdt.data = encode_gdt_entry(0, 0, 0, 0b10010010);

	tss = get_tss();
	gdt.tss.limit_low = (uint16_t)104 & 0xffff;
	gdt.tss.base_low = (uint16_t)((uint64_t)&tss & 0xffff);
	gdt.tss.base_mid = (uint8_t)(((uint64_t)&tss >> 16) & 0xffff);
	gdt.tss.access = 0x89;
	gdt.tss.limit_flags = 0x40;
	gdt.tss.limit_flags |= (uint8_t)((104 >> 16) & 0xff);
	gdt.tss.base_high = (uint8_t)(((uint64_t)&tss >> 24) & 0xff);
	gdt.tss.base_high2 = (uint32_t)(((uint64_t)&tss >> 32) & 0xffffffff);

	gdtr.size = (uint16_t)sizeof(gdt_t)-1;
	gdtr.offset = (uint64_t)&gdt;

	asm volatile("lgdt (%0)" : : "r" (&gdtr));
	asm volatile("ltr %0" : : "r" ((uint16_t)0x18));
}
