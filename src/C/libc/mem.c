#include "mem.h"

void memory_copy(unsigned char* src, unsigned char* dst, int size)
{
    for(int i = 0; i < size; i++)
        dst[i] = src[i];
}

void memory_set(u8* dst, u8 val, int size)
{
    for(int i = 0; i < size; i++)
        dst[i] = val;
}

u32 FREE_MEM_BASE = 0x10000;

u32 kmalloc(u32 size, int aligne, u32* physicalAddress)
{
    if(aligne == 1 && (FREE_MEM_BASE & 0xfffff000))
    {
        FREE_MEM_BASE &= 0xfffff000;
        FREE_MEM_BASE += 0x1000;
    }

    if(physicalAddress) *physicalAddress = FREE_MEM_BASE;

    u32 ret = FREE_MEM_BASE;

    FREE_MEM_BASE += size;
    return ret;
}