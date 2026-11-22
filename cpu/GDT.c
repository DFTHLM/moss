#include "GDT.h"

static struct gdt_entry GDT[5];
static struct gdt_ptr gdt_reg;

void gdt_flush(uint32_t gdt_ptr_addr);

void set_gdt_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    GDT[i].base_low = base & 0xFFFF;
    GDT[i].base_mid = (base >> 16) & 0xFF;
    GDT[i].base_high = (base >> 24) & 0xFF;

    GDT[i].limit_low = limit & 0xFFFF;
    GDT[i].limit_high_flags = ((limit >> 16) & 0x0F) | flags & 0xF0;

    GDT[i].access = access;
}

void init_gdt() {
    set_gdt_entry(0,0,0,0,0);
    set_gdt_entry(1, 0, 0xFFFF, KERNEL_CODE, FLAGS);
    set_gdt_entry(2, 0, 0xFFFF, KERNEL_DATA, FLAGS);
    set_gdt_entry(3, 0, 0xFFFF, USER_CODE, FLAGS);
    set_gdt_entry(4, 0, 0xFFFF, USER_DATA, FLAGS);

    gdt_reg.base = (uint32_t)&GDT;
    gdt_reg.limit = sizeof(GDT) - 1;

    gdt_flush((uint32_t)&gdt_reg);
}
