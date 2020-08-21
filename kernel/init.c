#include <stddef.h>
#include <stdint.h>
#include "init.h"
#include "gdt.h"

void kmain(){
	setup_gdt();
}
