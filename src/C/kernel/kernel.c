#include "kernel.h"

#include "print.h"

#include "isr.h"
#include "idt.h"

#include "timer.h"
#include "keyboard.h"

#include "string.h"


void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");
}

void user_input(char *input) 
{
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}
