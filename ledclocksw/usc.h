#ifndef __USC_H__
#define __USC_H__

#include <stdint.h>

#define HWUART_HASRECEIVED 0x1

extern volatile int16_t hwuart_byte;
extern volatile int16_t hwuart_flags;

void hwuart_sendb(uint8_t byte);
void hwuart_sendstr(char * ptr);

#endif // __USC_H__

