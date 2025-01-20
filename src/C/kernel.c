#include "print.h"
#include "utils.h"

#include "isr.h"
#include "idt.h"

#include "timer.h"
#include "keyboard.h"

void main()
{
    clear_screen();
    isr_install();

    asm volatile("sti");

    // init_timer(50);
    

    init_keyboard();
}
