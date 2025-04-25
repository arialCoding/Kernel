#include "ports.h"

void WB_port(unsigned short port, unsigned char byte)
{
    __asm__("out %%al, %%dx" : : "a" (byte), "d" (port));
}

unsigned char RB_port(unsigned short port)
{
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void WW_port(unsigned short port, unsigned short byte)
{
    __asm__("out %%ax, %%dx" : : "a" (byte), "d" (port));
}

unsigned short RW_port(unsigned short port)
{
    unsigned short res;
    __asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
    return res;
}