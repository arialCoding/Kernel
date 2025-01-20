#include "utils.h"

void memory_copy(unsigned char* src, unsigned char* dst, unsigned int size)
{
    for(int i = 0; i < size; i++)
        dst[i] = src[i];
}

void memory_set(u8* dst, u8 val, u32 size)
{
    for(int i = 0; i < size; i++)
        dst[i] = val;
}

void int_to_ascii(int n, char str[])
{
    int i, sign;

    if ((sign = n) < 0) n = -n;

    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);

}

int strlen(char str[])
{
    unsigned int count = 0;
    while(str[count]) count++;
    return count;
}

void reverse(char str[])
{
    int size = strlen(str);
    for(int i = 0; i < size/2; i++)
    {
        char temp = str[i];
        str[i] = str[size-1 - i];
        str[size-1 - i] = temp;
    }
}
