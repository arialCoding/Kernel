
;recieve in dx

printHex:
    pusha

    mov cx, 0

HEX_LOOP:
    cmp cx, 4
    je end

    mov ax, dx
    and ax, 0x000f
    add al, 0x30 ; get ascii of number

    cmp al, 0x39 ; test of bigger than 9
    jle step2

    add al, 7

step2:
    mov bx, OUTPUT + 5
    sub bx, cx
    mov [bx], al

    ror dx, 4

    add cx, 1
    jmp HEX_LOOP

end:
    mov bx, OUTPUT
    call print

    popa
    ret


OUTPUT db "0x0000", 0