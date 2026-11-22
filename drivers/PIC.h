#ifndef PIC_H
#define PIC_H

#include <stdbool.h>
#include <stdint.h>

extern void write_port(unsigned short port, char value);

void pic_init();
void pic_change_irq_status(uint8_t irq, bool enable);
void pic_send_eoi(unsigned short irq);

#endif
