#include <stddef.h>
#include <stdint.h>
#include "paging.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_tables[1024][1024] __attribute__((aligned(4096)));

extern void load_page_directory(uint32_t*);
extern void enable_paging();

void setup_paging(){
	for(int i = 0; i < 1024; i++){
		page_directory[i] = 0x00000002;
	}

	for(int i = 0; i < 1024; i++)
	{
		for(int j = 0; j < 1024; j++){
			// As the address is page aligned, it will always leave 12 bits zeroed.
			// Those bits are used by the attributes ;)
			page_tables[i][j] = ((i * 1024 * 0x1000) + j * 0x1000) | 3; // attributes: supervisor level, read/write, present.
		}
	}

	for(int i = 0; i < 1024; i++) page_directory[i] = ((uint32_t)page_tables[i]) | 3;

	load_page_directory(page_directory);
	enable_paging();
}
