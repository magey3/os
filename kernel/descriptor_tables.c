#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables.h"

extern void set_gdt(uint8_t* gdt, uint8_t size);

void encodeGdtEntry(uint8_t *target, struct GDT source)
{
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

void init_descriptor_tables(uint8_t* gdt){
	struct GDT gdt_s[3];
	gdt_s[0].base = 0;
	gdt_s[0].limit = 0;
	gdt_s[0].type = 0;

	gdt_s[1].base = 0;
	gdt_s[1].limit = 0xffffffff;
	gdt_s[1].type = 0x9a;

	gdt_s[2].base = 0;
	gdt_s[2].limit = 0xffffffff;
	gdt_s[2].type = 0x92;

	encodeGdtEntry(gdt, gdt_s[0]);
	encodeGdtEntry(gdt+8, gdt_s[1]);
	encodeGdtEntry(gdt+16, gdt_s[2]);

	set_gdt(gdt, 24);
}
