#include "isr.h"
#include "idt.h"

#include "print.h"
#include "ports.h"
#include "string.h"

#include "keyboard.h"
#include "timer.h"

isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install()
{
    set_IDT_gate(0, (uint32_t)isr0);
    set_IDT_gate(1, (uint32_t)isr1);
    set_IDT_gate(2, (uint32_t)isr2);
    set_IDT_gate(3, (uint32_t)isr3);
    set_IDT_gate(4, (uint32_t)isr4);
    set_IDT_gate(5, (uint32_t)isr5);
    set_IDT_gate(6, (uint32_t)isr6);
    set_IDT_gate(7, (uint32_t)isr7);
    set_IDT_gate(8, (uint32_t)isr8);
    set_IDT_gate(9, (uint32_t)isr9);
    set_IDT_gate(10, (uint32_t)isr10);
    set_IDT_gate(11, (uint32_t)isr11);
    set_IDT_gate(12, (uint32_t)isr12);
    set_IDT_gate(13, (uint32_t)isr13);
    set_IDT_gate(14, (uint32_t)isr14);
    set_IDT_gate(15, (uint32_t)isr15);
    set_IDT_gate(16, (uint32_t)isr16);
    set_IDT_gate(17, (uint32_t)isr17);
    set_IDT_gate(18, (uint32_t)isr18);
    set_IDT_gate(19, (uint32_t)isr19);
    set_IDT_gate(20, (uint32_t)isr20);
    set_IDT_gate(21, (uint32_t)isr21);
    set_IDT_gate(22, (uint32_t)isr22);
    set_IDT_gate(23, (uint32_t)isr23);
    set_IDT_gate(24, (uint32_t)isr24);
    set_IDT_gate(25, (uint32_t)isr25);
    set_IDT_gate(26, (uint32_t)isr26);
    set_IDT_gate(27, (uint32_t)isr27);
    set_IDT_gate(28, (uint32_t)isr28);
    set_IDT_gate(29, (uint32_t)isr29);
    set_IDT_gate(30, (uint32_t)isr30);
    set_IDT_gate(31, (uint32_t)isr31);

    // Remap the PIC
    WB_port(0x20, 0x11);
    WB_port(0xA0, 0x11);
    WB_port(0x21, 0x20);
    WB_port(0xA1, 0x28);
    WB_port(0x21, 0x04);
    WB_port(0xA1, 0x02);
    WB_port(0x21, 0x01);
    WB_port(0xA1, 0x01);
    WB_port(0x21, 0x0);
    WB_port(0xA1, 0x0); 

    // Install the IRQs
    set_IDT_gate(32, (uint32_t)irq0);
    set_IDT_gate(33, (uint32_t)irq1);
    set_IDT_gate(34, (uint32_t)irq2);
    set_IDT_gate(35, (uint32_t)irq3);
    set_IDT_gate(36, (uint32_t)irq4);
    set_IDT_gate(37, (uint32_t)irq5);
    set_IDT_gate(38, (uint32_t)irq6);
    set_IDT_gate(39, (uint32_t)irq7);
    set_IDT_gate(40, (uint32_t)irq8);
    set_IDT_gate(41, (uint32_t)irq9);
    set_IDT_gate(42, (uint32_t)irq10);
    set_IDT_gate(43, (uint32_t)irq11);
    set_IDT_gate(44, (uint32_t)irq12);
    set_IDT_gate(45, (uint32_t)irq13);
    set_IDT_gate(46, (uint32_t)irq14);
    set_IDT_gate(47, (uint32_t)irq15);

    set_IDT_descriptor(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t* r)
{
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r->int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r->int_no]);
    kprint("\n");
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t* r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r->int_no >= 40) WB_port(0xA0, 0x20); /* slave */
    WB_port(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
}

void irq_install()
{
    asm volatile("sti");

    init_timer(50);
    

    init_keyboard();
}

