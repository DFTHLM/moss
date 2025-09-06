#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stdbool.h>

extern void write_port(unsigned short port, char value);

#define VGA_MEMORY ((uint16_t*)0xB8000)
#define SCANCODE_MAX 256

typedef void (*key_handler_t)(void);

void init_special_keys();
void clear_vga_memory();
char convert_scancode(unsigned char scancode);
void putc(char c);
void puts(const char *str);

#endif
