#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
struct GDT {
	uint32_t base;
	uint32_t limit;
	uint8_t type;
};

typedef struct {
	uint16_t link;
	uint16_t res0;
	uint32_t esp0;
	uint16_t ss0;
	uint16_t res1;
	uint32_t esp1;
	uint16_t ss1;
	uint16_t res2;
	uint32_t esp2;
	uint16_t ss2;
	uint16_t res3;
	uint32_t cr3, eip, eflags, eax, cx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es;
	uint16_t res4;
	uint16_t cs;
	uint16_t res5;
	uint16_t ss;
	uint16_t res6;
	uint16_t ds;
	uint16_t res7;
	uint16_t fs;
	uint16_t res8;
	uint16_t gs;
	uint16_t res9;
	uint16_t ldtr;
	uint32_t res10;
	uint16_t iopb;
} __attribute__((packed)) TSS;

void init_descriptor_tables();
#endif
