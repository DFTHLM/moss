#include "qemu_debug.h"

void dputc(char c){
    write_port(QEMU_PORT, c);
}

int dprintf(const char *str, int len){
    while (*str != *"\0"){
        dputc(*str++);
    }

    return 0;
}

