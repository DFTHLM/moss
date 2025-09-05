#include "kernel.h"

static const char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void kernel_main(void)
{
	char *vidptr = (char*)0xb8000;
	unsigned int j = 0;

	while(j < 80 * 25 * 2) {
		vidptr[j] = ' ';
		vidptr[j+1] = 0x07; 		
		j = j + 2;
	}

    pic_init();
    keyboard_init();
    idt_init();
    pic_change_irq_status(KEYBOARD_IRQ, true);
    asm volatile("sti");
    j = 0;

    while (1) {
        asm volatile("hlt");
        uint8_t scancode = get_scancode();
        if (!scancode) continue;
        if (scancode & 0x80) continue; // ignore key release

        char c = scancode_to_ascii[scancode];
        if (!c) continue;

        vidptr[j] = c;
        vidptr[j+1] = 0x07;
        j += 2;
    }
}
