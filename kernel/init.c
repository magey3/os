#include <stddef.h>
#include <stdint.h>
#include "init.h"
#include "gdt.h"
#include "idt.h"
#include "io/vga/mtxt_print.h"

void kmain(){
	setup_gdt();
	setup_idt();

	asm volatile("int $0x80");
}
