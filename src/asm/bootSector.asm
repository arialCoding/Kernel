[org 0x7C00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, RM_MSG
call print
call print_nl

call kernelLoad

call switch

jmp $

%include "src/asm/include/print.asm"
%include "src/asm/include/printHex.asm"
%include "src/asm/include/diskLoad.asm"
%include "src/asm/include/GDT.asm"
%include "src/asm/include/switch32.asm"
%include "src/asm/include/print32.asm"

[bits 16]
kernelLoad:
    mov bx, KL_MSG
    call print
    call print_nl

    mov bx, KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call diskLoad
    ret

[bits 32]

BEGIN_protectedMode:
    call KERNEL_OFFSET
    jmp $


RM_MSG db "in real mode", 0
PM_MSG db "in protected mode", 0
KL_MSG db "loading kernel . . .", 0

BOOT_DRIVE db 0

times 510 - ($ - $$) db 0
dw 0xAA55