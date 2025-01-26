#include "mem.h"

void memory_copy(unsigned char* src, unsigned char* dst, int size)
{
    for(int i = 0; i < size; i++)
        dst[i] = src[i];
}

void memory_set(uint8_t* dst, uint8_t val, int size)
{
    for(int i = 0; i < size; i++)
        dst[i] = val;
}

uint32_t FREE_MEM_BASE = 0x10000;

uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr)
{
    if (align == 1 && (FREE_MEM_BASE & 0xFFFFF000)) {
        FREE_MEM_BASE &= 0xFFFFF000;
        FREE_MEM_BASE += 0x1000;
    }

    if (phys_addr) *phys_addr = FREE_MEM_BASE;

    uint32_t ret = FREE_MEM_BASE;
    FREE_MEM_BASE += size;
    return ret;
}
