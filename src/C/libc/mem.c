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