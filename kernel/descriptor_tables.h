#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
struct GDT {
	uint32_t base;
	uint32_t limit;
	uint8_t type;
};

void init_descriptor_tables();
#endif
