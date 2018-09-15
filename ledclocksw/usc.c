#include <msp430.h>
#include <stdint.h>
#include <stddef.h>

#include "usc.h"

volatile int16_t hwuart_byte;
volatile int16_t hwuart_flags;
volatile int16_t hwuart_pos;
volatile int8_t * hwuart_linebuf;
volatile int8_t hwuart_linebuf_a[28];
volatile int8_t hwuart_linebuf_b[28];

void hwuart_init() {
	hwuart_linebuf = hwuart_linebuf_a;
	hwuart_pos = 0;
}

void hwuart_sendb(uint8_t byte) {
	UCA0TXBUF = byte;
	while(!(IFG2 & UCA0TXIFG)) { __nop(); }
}

void hwuart_sendstr(char * ptr) {
	while (*ptr != '\0') {
		UCA0TXBUF = *ptr++;
		while(!(IFG2 & UCA0TXIFG)) { __nop(); }
	}
}

int8_t * hwuart_getlinebuf() {
	if (hwuart_linebuf == hwuart_linebuf_b) {
		return hwuart_linebuf_a;
	}
	return hwuart_linebuf_b;
}

void USCI0RX_ISR(void) __attribute__((interrupt(USCIAB0RX_VECTOR)));
void USCI0RX_ISR(void) {
	if (IFG2 & UCA0RXIFG) {
		// Kick off the CPU on a CR (\r) or (\n)
		hwuart_byte = UCA0RXBUF;
		if (hwuart_pos <= 27) {
			if (hwuart_byte == '\r' || hwuart_byte == '\n') {
				if (hwuart_pos != 0) {
					hwuart_linebuf[hwuart_pos] = '\0';
					if (hwuart_linebuf == hwuart_linebuf_a) {
						hwuart_linebuf = hwuart_linebuf_b;
					} else {
						hwuart_linebuf = hwuart_linebuf_a;
					}
					hwuart_pos = 0;
					hwuart_flags |= HWUART_HASRECEIVED;
					__bic_SR_register_on_exit(CPUOFF);
				}
			} else {
				UCA0TXBUF = hwuart_byte;
				hwuart_linebuf[hwuart_pos] = hwuart_byte;
				hwuart_pos ++;
			}
		} else {
			hwuart_pos = 0;
		}
		//hwuart_byte = UCA0RXBUF;
		//hwuart_flags |= HWUART_HASRECEIVED;
		//__bic_SR_register_on_exit(CPUOFF);
	}
}

void USCI0TX_ISR(void) __attribute__((interrupt(USCIAB0TX_VECTOR)));
void USCI0TX_ISR(void) {
	//
}


