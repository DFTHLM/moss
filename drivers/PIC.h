#ifndef PIC_H
#define PIC_H

#include <stdbool.h>

extern void write_port(unsigned short port, char value);

void pic_init();
void pic_change_irq_status(char irq, bool enable);
void pic_send_eoi(unsigned short irq);

#endif
