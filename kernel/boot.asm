bits 32
section .text
        align 4
        dd 0x1BADB002            ;magic number for GRUB
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00)

global start
extern kernel_main

start:
  cli
  mov esp, stack_space + 0x4000
  call kernel_main
  hlt

section .bss
resb 0x4000
stack_space:
