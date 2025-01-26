#ifndef MEM_H
#define MEM_H

#include "type.h"

void memory_copy(unsigned char* src, unsigned char* dst, int size);
void memory_set(u8* dst, u8 val, int size);

u32 kmalloc(u32 size, int aligne, u32* physicalAddress);

#endif // MEM_H