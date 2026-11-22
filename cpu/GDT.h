#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define KERNEL_CODE 0x9B
#define KERNEL_DATA 0x93

#define USER_CODE 0xFB
#define USER_DATA 0xF3

#define FLAGS 0xC0

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_high_flags;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));


void gdt_flush(uint32_t gdt_ptr_addr);
void set_gdt_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void init_gdt();

#endif
