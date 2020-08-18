#include <stddef.h>
#include <stdint.h>
#include "io/speaker.h"
#include "io/io.h"

#define PIT_FREQUENCY 1193180

void play_sound(uint32_t frequency){
	uint32_t div = PIT_FREQUENCY / frequency;

	outb(0x43, 0xb6);
	outb(0x42, (uint8_t)(div));
	outb(0x42, (uint8_t)(div >> 8));

	uint8_t tmp = inb(0x61);
	if(tmp != (tmp | 3)){
		outb(0x61, tmp | 3);
	}
}

void stop_sound() {
	uint8_t tmp = inb(0x61) & 0xfc;
	outb(0x61, tmp);
}

void beep() {
	
}
