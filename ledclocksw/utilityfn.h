#ifndef __UTILITYFN_H__
#define __UTILITYFN_H__

#include <stdint.h>

void Utility_delay(unsigned short int loops);

unsigned long int Utility_hexToInt(const char* s, int count);
void Utility_intToHex(char* dst, const void* ptr, int count);

uint16_t Utility_uint16_beToLe(const void * ptr);

#endif // __UTILITYFN_H__
