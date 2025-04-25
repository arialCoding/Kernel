#include "idt.h"

IDT_Entry IDT[IDT_ENTRIES];
IDT_Descriptor IDT_Desc;

void set_IDT_gate(int gate, uint32_t handler_address)
{
    IDT[gate].offset_low = low_16(handler_address);
    IDT[gate].segment_selector = CODE_SEGMENT_OFFSET;
    IDT[gate].reserved = 0;
    IDT[gate].flags = 0x8E; // 1000 1110
    IDT[gate].offset_high = high_16(handler_address);
}

void set_IDT_descriptor()
{
    IDT_Desc.base = (uint32_t)&IDT;
    IDT_Desc.size = IDT_ENTRIES*sizeof(IDT_Entry) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&IDT_Desc));
}
