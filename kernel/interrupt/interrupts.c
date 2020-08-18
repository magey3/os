#include <stddef.h>
#include <stdint.h>
#include "interrupt/interrupts.h"
#include "io/speaker.h"
#include "io/io.h"
#define EOI outb(0x20, 0x20);

__attribute__((interrupt)) void irq80(stack_frame* frame){
	play_sound(1000);
	for(;;);
	EOI
}
