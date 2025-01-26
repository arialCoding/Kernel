#include "kernel.h"

#include "print.h"

#include "isr.h"
#include "idt.h"

#include "timer.h"
#include "keyboard.h"

#include "string.h"
#include "mem.h"



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
    } else if (strcmp(input, "INFO") == 0) {
        kprint("visit https://github.com/arialCoding/kernel for more info!\n");
    }else if (strcmp(input, "PAGE") == 0) {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }

    kprint("\n> ");
}
