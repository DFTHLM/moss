#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/IDT.h"
#include "PIC.h"

#define KEYBOARD_IRQ 1
#define KEYBOARD_DATA_PORT 0x60

extern void keyboard_handler(void);
extern uint8_t read_port(char port);

void keyboard_init();
uint8_t get_scancode();

#endif
