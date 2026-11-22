#include "kernel.h"

void kernel_main(void)
{
    // initialize everything
    init_gdt();
    pic_init();
    keyboard_init();
    idt_init();
    idt_init_exceptions();
    // enable the irq only after idt has a way to handle the interrupt
    pic_change_irq_status(KEYBOARD_IRQ, true);
    init_tty();

    // enable interrupts after initializing the IDT and PIC so they dont recieve them sooner
    asm volatile("sti");
    dprintf("test", 4);

    while (1) {
        asm volatile("hlt");
        uint8_t scancode = get_scancode();

        char c = convert_scancode(scancode);

        tty_write(&c, 1);
    }
}
