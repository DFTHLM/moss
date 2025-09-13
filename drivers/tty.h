#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stdbool.h>
#include "../misc/ring_buffer.h"

extern void write_port(unsigned short port, char value);

#define VGA_MEMORY ((uint16_t*)0xB8000)
#define SCANCODE_MAX 256

typedef void (*key_handler_t)(void);

char convert_scancode(unsigned char scancode);
void init_tty();
int tty_write(const char *str, int len);
int tty_read(char *buf, int maxlen);

#endif
