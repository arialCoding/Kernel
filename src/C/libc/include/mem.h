#ifndef MEM_H
#define MEM_H

#include "types.h"

void memory_copy(unsigned char* src, unsigned char* dst, int size);
void memory_set(u8* dst, u8 val, int size);

#endif // MEM_H