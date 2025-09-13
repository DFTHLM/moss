global write_port
write_port:
    mov dx, [esp + 4] ; port
    mov al, [esp + 8] ; value
    out dx, al
    ret

global read_port
read_port:
    mov dx, [esp + 4] ; port
    in al, dx
    ret 
