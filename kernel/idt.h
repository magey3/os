#ifndef IDT_H
#define IDT_H

typedef struct {
	uint16_t offset_low;
	uint16_t cs;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t size;
	idt_entry_t* offset;
} __attribute__((packed)) idtr_t;

void setup_idt();

#endif
