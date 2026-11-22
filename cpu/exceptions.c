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

void exception_handler(struct regs *r)
{
    const char *interrupt = exception_names[r->int_no]; 
    dprintf(interrupt, 0);
    for (;;) __asm__ volatile ("cli; hlt"); //halt for now, TODO: extend later
}
