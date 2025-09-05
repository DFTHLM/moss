#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#define IDT_SIZE 256

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base; 
}__attribute__((packed));

void set_idt_entry(int vector, unsigned long handler, uint16_t selector, uint8_t type_attr);
void idt_init();

#endif
