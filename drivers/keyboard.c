#include "keyboard.h"

uint8_t scancode;

void keyboard_init() {
    // sets the idt entry at 0x21 with the pointer to the asm stub
    // selector is 0x08 -> 
    // type attribute is 0x8E
    set_idt_entry(0x21, (unsigned long)keyboard_handler, 0x08, 0x8E);
}

void keyboard_handler_c() {
    // just returns the pure scancode as its handled by the tty code
    scancode = read_port(KEYBOARD_DATA_PORT);
    // send an eoi otherwise bad things happen
    pic_send_eoi(KEYBOARD_IRQ);
}

uint8_t get_scancode() {
    return scancode;
}

