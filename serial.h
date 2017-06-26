#ifndef __SERIAL_H
#define __SERIAL_H

int initSerial(const char *device, const int baund);
void readSerial (int fd);

#endif
