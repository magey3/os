#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables.h"
#include "paging.h"
#include "multiboot.h"
#include "kernel.h"
#include "init.h"

void init(multiboot_info_t* mbd, uint32_t magic){
	mb_mmap_entry_t* mmap_entry = mbd->mmap_addr;
	
	init_descriptor_tables();
	setup_paging();
	
	print(mmap_entry->size);

	kmain();
}
