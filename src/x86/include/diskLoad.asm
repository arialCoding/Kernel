; load 'dh' sectors from drive 'dl' into ES:BX
diskLoad:
    pusha
    push dx

    mov ah, 2
    
    mov al, dh ; number of sectors
    mov ch, 0 ; cyllinder
    mov cl, 2 ; sector
    mov dh, 0 ; head

    int 0x13

    jc DISK_ERROR

    pop dx
    cmp dh, al
    jne SECTOR_ERROR

    popa
    ret

DISK_ERROR:
    mov bx, DISK_ERROR_MSG
    call print
    mov dh, ah
    call printHex
    jmp DISK_LOOP

SECTOR_ERROR:
    mov bx, SECTOR_ERROR_MSG
    call print

DISK_LOOP:
    jmp $

DISK_ERROR_MSG db "Failed to read disk! ERR code: ", 0

SECTOR_ERROR_MSG db "Wrong number of sectors read!", 0

