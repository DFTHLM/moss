#include "IDT.h"

struct idt_entry IDT[IDT_SIZE];
struct idt_ptr idt_reg;

// IDT is the idt table it will work with
// only init the idt after filling every field you want to use
void set_idt_entry(int vector, unsigned long handler, uint16_t selector, uint8_t type_attr) {
    IDT[vector].offset_low  = handler & 0xFFFF;
    IDT[vector].selector    = selector;
    IDT[vector].zero        = 0;
    IDT[vector].type_attr   = type_attr;
    IDT[vector].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() {
    idt_reg.limit = sizeof(struct idt_entry) * IDT_SIZE - 1;
    idt_reg.base  = (uint32_t)&IDT;

    asm volatile("lidt (%0)" : : "r"(&idt_reg));
}

