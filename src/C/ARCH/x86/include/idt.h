#ifndef IDT_H
#define IDT_H

#include "type.h"

#define CODE_SEGMENT_OFFSET 0x08

typedef struct
{
    uint16_t offset_low;
    uint16_t segment_selector;

    uint8_t reserved;

    uint8_t flags;

    uint16_t offset_high;
} __attribute__((packed)) IDT_Entry;

typedef struct
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed)) IDT_Descriptor;

#define IDT_ENTRIES 256

extern IDT_Entry IDT[IDT_ENTRIES];
extern IDT_Descriptor IDT_Desc;


void set_IDT_gate(int gate, uint32_t handler_address);
void set_IDT_descriptor();


#endif // IDT_H