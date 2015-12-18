#ifndef __SERVERSOCKET_H
#define __SERVERSOCKET_H

void ServerSocketTCP(void);

void eztoa(char * buf, int val, int base);
void rrtoa(char * buf, unsigned val, int base);
void longtoa(char * buf, unsigned long val, int base);

#endif