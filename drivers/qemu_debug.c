#include "qemu_debug.h"

void dputc(char c){
    write_port(QEMU_PORT, c);
}

void dputs(const char *str){
    while (*str != '\0'){
        dputc(*str++);
    }
}

void unsigned_handler(uint32_t num){
    const char digits[32] = {};

    while (num > 0){
        // TODO: finish
    }
}

void dprintf(const char *str, ...){
    va_list ap;
    va_start(ap, str);
    while (*str != '\0'){
        if (*str == '%'){
            char next = *(str + 1);
            if (next == 's'){
                str += 2;
                const char *string = va_arg(ap, const char *);
                if (string == ((void *)0)){
                    dputs("(null)");
                    continue;
                }
                dputs(string);
                continue;
            } else if (next == 'c'){
                str += 2;
                int number = va_arg(ap, int);
                dputc((char)number);
                continue;
            } else if (next == '%') {
                str += 2;
                dputc('%');
                continue;
            }
        }
        dputc(*str++);
    }

    va_end(ap);
}

