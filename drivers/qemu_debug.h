#ifndef QEMU_DEBUG
#define QEMU_DEBUG

#include <stdarg.h>
#include <stdint.h>

#define QEMU_PORT 0xE9

void dprintf(const char *str, ...);
extern void write_port(unsigned short port, char value);

#endif
