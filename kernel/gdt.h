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
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_flags;
	uint8_t base_high;
	uint32_t base_high2;
	uint32_t reserved;
} __attribute__((packed)) gdt_tss_entry_t;

typedef struct {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) gdtr_t;

typedef struct {
	gdt_entry_t null;
	gdt_entry_t code;
	gdt_entry_t data;
	gdt_tss_entry_t tss;

} __attribute__((packed)) gdt_t;

void setup_gdt();

#endif
