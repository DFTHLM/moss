#ifndef QEMU_DEBUG
#define QEMU_DEBUG

#define QEMU_PORT 0xE9

int dprintf(const char *str, int len);
extern void write_port(unsigned short port, char value);

#endif
