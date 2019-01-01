#ifndef __USC_H__
#define __USC_H__

#include <stdint.h>

#define HWUART_HASRECEIVED (0x1)

//extern volatile int16_t hwuart_byte;
extern volatile int16_t hwuart_flags;
extern volatile int16_t hwuart_pos;
extern volatile int8_t hwuart_linebuf_a[];
extern volatile int8_t hwuart_linebuf_b[];

void hwuart_init();
void hwuart_sendb(uint8_t byte);
void hwuart_sendstr(char * ptr);
int8_t * hwuart_getlinebuf();

#endif // __USC_H__

