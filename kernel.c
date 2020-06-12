#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

#define FG_BLACK 0x0
#define FG_BLUE 0x1
#define FG_GREEN 0x2
#define FG_CYAN 0x3
#define FG_RED 0x4
#define FG_MAGENTA 0x5 
#define FG_BROWN 0x6
#define FG_GRAY 0x7
#define FG_DARK_GRAY 0x8
#define FG_BRIGHT_BLUE 0x9
#define FG_BRIGHT_GREEN 0xa
#define FG_BRIGHT_CYAN 0xb
#define FG_BRIGHT_RED 0xc
#define FG_BRIGHT_MAGENTA 0xd 
#define FG_YELLOW 0xe
#define FG_WHITE 0xf

#define BG_BLACK 0x00 
#define BG_BLUE 0x10
#define BG_GREEN 0x20
#define BG_CYAN 0x30
#define BG_RED 0x40
#define BG_MAGENTA 0x50
#define BG_BROWN 0x60
#define BG_GRAY 0x70
#define BG_DARK_GRAY 0x80
#define BG_BRIGHT_BLUE 0x90
#define BG_BRIGHT_GREEN 0xa0
#define BG_BRIGHT_CYAN 0xb0
#define BG_BRIGHT_RED 0xc0
#define BG_BRIGHT_MAGENTA 0xd0
#define BG_YELLOW 0xe0
#define BG_WHITE 0xf0

volatile uint16_t* vga_buffer = (uint16_t*)0xb8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_color = BG_BLACK | FG_WHITE;

void term_init(){
	for(int col = 0; col < VGA_COLS; col++){
		for(int row = 0; row < VGA_ROWS; row++){
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
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
				vga_buffer[index] = ((uint16_t)term_color << 8) | c;
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
	
	term_color = BG_BLACK | FG_GREEN;
	print("Hello world!\n");
	print("Welcome to the kernel.\n");
}
