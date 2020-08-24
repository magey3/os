#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "tss.h"

gdt_t gdt;
gdtr_t gdtr;
tss_t tss;

void encode_gdt_entry(gdt_entry_t* entry, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access){
	entry->limit_low = (uint16_t)(limit & 0xffff);
	entry->base_low = (uint16_t)(base & 0xffff);
	entry->base_mid = (uint8_t)((base >> 16) & 0xff);
	entry->access = access;
	entry->limit_flags = (flags << 4) & 0xf0;
	entry->limit_flags |= (uint8_t)((limit >> 16) & 0xf);
	entry->base_high = (uint8_t)((base >> 24) & 0xff);
}
//0b1010, 0b10011010
void setup_gdt(){
	encode_gdt_entry(&gdt.null, 0, 0, 0, 0);
	encode_gdt_entry(&gdt.code, 0, 0xffffffff, 0b1010, 0b10011010);
	encode_gdt_entry(&gdt.data, 0, 0, 0, 0b10010010);

	get_tss(&tss);
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
	asm volatile("mov $0x10, %ax");
	asm volatile("mov %ax, %ds");
	asm volatile("mov %ax, %ss");
	asm volatile("mov %ax, %es");
	asm volatile("mov %ax, %fs");
	asm volatile("mov %ax, %gs");
	asm volatile("ltr %0" : : "r" ((uint16_t)0x18));
}
