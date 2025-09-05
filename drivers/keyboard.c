#include "keyboard.h"

uint8_t scancode;

void keyboard_init() {
    set_idt_entry(0x21, (unsigned long)keyboard_handler, 0x08, 0x8E);
}

void keyboard_handler_c() {
    scancode = read_port(KEYBOARD_DATA_PORT);
    pic_send_eoi(KEYBOARD_IRQ);
}

uint8_t get_scancode() {
    return scancode;
}

