#ifndef PORTS_H
#define PORTS_H

void WB_port(unsigned short port, unsigned char byte);
unsigned char RB_port(unsigned short port);
void WW_port(unsigned short port, unsigned short byte);
unsigned short RW_port(unsigned short port);

#endif // PORTS_H
