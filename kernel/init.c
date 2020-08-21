#include <stddef.h>
#include <stdint.h>
#include "init.h"
#include "gdt.h"
#include "idt.h"

void kmain(){
	setup_gdt();
	setup_idt();
}
