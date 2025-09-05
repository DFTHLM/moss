#include "PIC.h"

static char master_mask = 0xFF;
static char slave_mask = 0xFF;

void pic_init() {
    // Start initialization
    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);

    // Remap offsets
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);

    // Cascading
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);

    // Environment
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);

    // Mask all IRQs initially
    write_port(0x21, 0xFF);
    write_port(0xA1, 0xFF);
}

void pic_change_irq_status(char irq, bool enable) {
    if (irq < 8) {
        if (enable) {
            master_mask &= ~(1 << irq);
        } else {
            master_mask |= (1 << irq);
        }
        write_port(0x21, master_mask);
    } else {
        irq -= 8;
        if (enable) {
            slave_mask &= ~(1 << irq);
        } else {
            slave_mask |= (1 << irq);
        }
        write_port(0xA1, slave_mask);
    }
}

void pic_send_eoi(unsigned short irq) {
    if (irq >= 8) {
        write_port(0xA0, 0x20);
    };
    write_port(0x20, 0x20);
}
