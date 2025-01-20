#ifndef IDT_H
#define IDT_H

#include "types.h"

#define CODE_SEGMENT_OFFSET 0x08

typedef struct
{
    u16 offset_low;
    u16 segment_selector;

    u8 reserved;

    u8 flags;

    u16 offset_high;
} __attribute__((packed)) IDT_Entry;

typedef struct
{
    u16 size;
    u32 base;
} __attribute__((packed)) IDT_Descriptor;

#define IDT_ENTRIES 256

extern IDT_Entry IDT[IDT_ENTRIES];
extern IDT_Descriptor IDT_Desc;


void set_IDT_gate(int gate, u32 handler_address);
void set_IDT_descriptor();


#endif // IDT_H