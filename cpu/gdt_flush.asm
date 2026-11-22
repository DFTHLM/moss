;flushes and inits the newly created interrupt handlers

global gdt_flush
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, 0x10        ; kernel data selector (entry 2 * 8)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.reload_cs ; far jump reloads CS (kernel code, entry 1 * 8)
.reload_cs:
    ret
