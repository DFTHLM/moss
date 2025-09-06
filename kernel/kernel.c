#include "kernel.h"

void kernel_main(void)
{
    clear_vga_memory();

    pic_init();
    keyboard_init();
    idt_init();
    pic_change_irq_status(KEYBOARD_IRQ, true);
    init_special_keys();
    asm volatile("sti");

    while (1) {
        asm volatile("hlt");
        uint8_t scancode = get_scancode();

        char c = convert_scancode(scancode);
        if (!c) continue;

        putc(c);
    }
}
