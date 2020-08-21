#ifndef GDT_H
#define GDT_H

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_flags;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t size;
	gdt_entry_t* offset;
} __attribute__((packed)) gdtr_t;

void setup_gdt();

#endif
