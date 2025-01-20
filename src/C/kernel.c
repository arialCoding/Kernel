#include "print.h"
#include "utils.h"

#include "isr.h"
#include "idt.h"

void main() {
    clear_screen();
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
