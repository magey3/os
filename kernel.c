#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

#define BLINK 0b10000000

volatile uint16_t* vga_buffer = (uint16_t*)0xb8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_char_attrib = 0x0a;

void term_init(){
	for(int col = 0; col < VGA_COLS; col++){
		for(int row = 0; row < VGA_ROWS; row++){
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_char_attrib << 8) | ' ';
		}
	}
}

void putc(char c){
	switch(c){
		case '\n':
			{
				term_col = 0;
				term_row++;
				break;
	
			}
		default:
			{
				const size_t index = (VGA_COLS * term_row) + term_col;
				vga_buffer[index] = ((uint16_t)term_char_attrib << 8) | c;
				term_col++;
				break;
			}
	}
}


void print(const char* str){
	for(size_t i = 0; str[i] != '\0'; i++)
		putc(str[i]);
}

void kernel_main(){
	term_init();
	
	term_char_attrib = term_char_attrib | BLINK;
	print("Hello world!\n");
	print("Welcome to the kernel.\n");
}
