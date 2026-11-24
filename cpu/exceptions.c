#include "exceptions.h"

// register handlers for all interrupts 0 to 31 (cpu interrupts)

void idt_init_exceptions(void)
{
    for (uint8_t i = 0; i < 32; i++){
        set_idt_entry(i, isr_stub_table[i], 0x08, 0x8E);
    }
}

// a common handler for all exceptions
// TODO: Extend for 8, 10 to 14, 17, 21, 29 and 30
// TODO: to handle error codes (helpful!!!!!)

void selector_handler(uint32_t error) {
    // External:
    
    if (error & 1) {
        dprintf("External; ");
    }

    // Tbl:
    if (error & 0x1) {
        dprintf("IDT; ");
    } else {
        if (error & 2) {
            dprintf("LDT; ");
        } else {
            dprintf("GDT; ");
        }
    }

    uint32_t selector = error & 0x3;
    dprintf("0x%x\n", selector);
}

void exception_handler(struct regs *r)
{
    const char *interrupt = exception_names[r->int_no]; 
    dprintf("%s\n", interrupt);
    if (r->int_no >= 10 && r->int_no < 14) {
        selector_handler(r->err_code);
    }
    for (;;) __asm__ volatile ("cli; hlt"); //halt for now, TODO: extend later
}
