#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <stdint.h>
#include "IDT.h"
#include "../drivers/PIC.h"
#include "../drivers/qemu_debug.h"

static const char *exception_names[32] = {
    "Division Error",                 // 0  #DE
    "Debug",                          // 1  #DB
    "Non-maskable Interrupt",         // 2
    "Breakpoint",                     // 3  #BP
    "Overflow",                       // 4  #OF
    "Bound Range Exceeded",           // 5  #BR
    "Invalid Opcode",                 // 6  #UD
    "Device Not Available",           // 7  #NM
    "Double Fault",                   // 8  #DF
    "Coprocessor Segment Overrun",    // 9
    "Invalid TSS",                    // 10 #TS
    "Segment Not Present",            // 11 #NP
    "Stack-Segment Fault",            // 12 #SS
    "General Protection Fault",       // 13 #GP
    "Page Fault",                     // 14 #PF
    "Reserved",                       // 15
    "x87 Floating-Point Exception",   // 16 #MF
    "Alignment Check",               // 17 #AC
    "Machine Check",                  // 18 #MC
    "SIMD Floating-Point Exception",  // 19 #XM
    "Virtualization Exception",       // 20 #VE
    "Control Protection Exception",   // 21 #CP
    "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", // 22-27
    "Hypervisor Injection Exception", // 28 #HV
    "VMM Communication Exception",    // 29 #VC
    "Security Exception",             // 30 #SX
    "Reserved",                       // 31
};


struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;  // pusha order
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags;                // pushed by CPU
    uint32_t user_esp, ss;                   // only valid if from ring 3
};

extern uint32_t isr_stub_table[32];

void idt_init_exceptions(void);

void exception_handler(struct regs *r);

#endif
