[bits 16]

switch:
    cli
    lgdt [gdt_descriptor]
    ; set Protected mofe bit
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    ; flush CPU
    jmp CODE_SEG:init_protectedMode

[bits 32]

init_protectedMode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_protectedMode