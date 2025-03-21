org 0x7c00

KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_to_pm
    jmp $ ; never executed

%include "boot/print.asm"
%include "boot/print_hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32bit_print.asm"
%include "boot/switch_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    ;mov dl, 0x80 ; floppy = 0x0, hdd = 0x80
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0

MSG_REAL_MODE db "Started in 16bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

clear_screen:
    pusha
    mov ah, 0x06    ; Scroll up function
    mov al, 0x00    ; Clear entire screen
    mov bh, 0x07    ; Attribute (white on black)
    mov cx, 0x0000  ; Top-left corner (0,0)
    mov dx, 0x184f  ; Bottom-right corner (24,79)
    int 0x10        ; Call BIOS interrupt
    popa
    ret

times 510 - ($-$$) db 0
dw 0xaa55
