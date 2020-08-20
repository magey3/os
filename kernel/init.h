#ifndef INIT_H
#define INIT_H

typedef struct {
	uint32_t size;
	uint32_t base_addr_low, base_addr_high;
	uint32_t lenght_low, legnth_high;
	uint32_t type;
} __attribute__((packed)) mb_mmap_entry_t;

void init(multiboot_info_t* mbt, uint32_t magic);

#endif
