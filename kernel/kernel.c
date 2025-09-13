#include "kernel.h"

void kernel_main(void)
{
    // initialize everything
    pic_init();
    keyboard_init();
    idt_init();
    // enable the irq only after idt has a way to handle the interrupt
    pic_change_irq_status(KEYBOARD_IRQ, true);
    init_tty();

    // enable interrupts after initializing the IDT and PIC so they dont recieve them sooner
    asm volatile("sti");

    while (1) {
        asm volatile("hlt");
        uint8_t scancode = get_scancode();

        char c = convert_scancode(scancode);
        if (!c) continue;

        tty_write(&c, 1);
    }
}
