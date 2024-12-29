#include "ports.h"

void main() {
    
    WB_port(0x3d4, 14); 

    int position = RB_port(0x3d5);
    position = position << 8;

    WB_port(0x3d4, 15); 
    position += RB_port(0x3d5);

    int offset_from_vga = position * 2;

   
    char* vga = (char*)0xb8000;
    vga[offset_from_vga] = '#'; 
    vga[offset_from_vga+1] = 0x0f;
}
