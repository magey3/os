#ifndef IO_H
#define IO_h
// Sends given data to given I/O port
extern void outb(uint8_t port, uint8_t data);

// Gets data from given I/O port
extern uint8_t inb(uint8_t port);

#endif
