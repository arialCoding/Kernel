#ifndef UTILS_H
#define UTILS_H

#include "types.h"

void memory_copy(unsigned char* src, unsigned char* dst, unsigned int size);
void memory_set(u8* dst, u8 val, u32 size);

void int_to_ascii(int n, char str[]);

void reverse(char str[]);
int strlen(char str[]);

#endif // UTILS_H