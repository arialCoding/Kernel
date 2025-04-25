#ifndef MEM_H
#define MEM_H

#include "type.h"
#include "stddef.h"

void memory_copy(unsigned char* src, unsigned char* dst, int size);
void memory_set(uint8_t* dst, uint8_t val, int size);

uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr);

#endif // MEM_H