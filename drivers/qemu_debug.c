#include "qemu_debug.h"

void dputc(char c){
    write_port(QEMU_PORT, c);
}

void dputs(const char *str){
    while (*str != '\0'){
        dputc(*str++);
    }
}

void unsigned_handler(uint32_t num, int base){
    if (num == 0) {
        dputc('0');
        return;
    }

    char digits[32] = {0};
    int length = 0;
    const char *lookup = "0123456789abcdef";

    while (num > 0){
        digits[length] = lookup[num % base];
        length++;
        num /= base;
    }

    for (int i = length - 1; i >= 0; i--) {
        dputc(digits[i]);
    }
}

void signed_handler(int num){
    uint32_t unsigned_num;

    if (num < 0){
        dputc('-');
        unsigned_num = -(uint32_t)num;
    } else {
        unsigned_num = (uint32_t)num;
    }

    unsigned_handler(unsigned_num, 10);
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

            } else if (next == 'u') {
                str += 2;
                uint32_t num = va_arg(ap, uint32_t);
                unsigned_handler(num, 10);
                continue;

            } else if (next == 'd') {
                str += 2;
                int num = va_arg(ap, int);
                signed_handler(num);
                continue;

            } else if (next == 'x'){
                str += 2;
                uint32_t num = va_arg(ap, uint32_t);
                unsigned_handler(num, 16);
                continue;
            }
        }

        dputc(*str++);
    }

    va_end(ap);
}

