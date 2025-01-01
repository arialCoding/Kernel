;recieve in bx
print:
    pusha

print_loop:

    mov al, [bx]
    cmp al, 0
    je done

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp print_loop

done:
    popa
    ret

print_nl:
    pusha
    
    mov ah, 0x0e
    
    mov al, 0x0a ; \n new line
    int 0x10
   
    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

clear_screen:
    pusha

    mov ah, 0x00
    mov al, 0x03
    int 0x10

    popa
    ret