#include <msp430.h>
#include <stdint.h>
#include <stddef.h>

#include "usc.h"

volatile int16_t hwuart_byte;
volatile int16_t hwuart_flags;

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

void USCI0RX_ISR(void) __attribute__((interrupt(USCIAB0RX_VECTOR)));
void USCI0RX_ISR(void) {
	if (IFG2 & UCA0RXIFG) {
		hwuart_byte = UCA0RXBUF;
		hwuart_flags |= HWUART_HASRECEIVED;
		__bic_SR_register_on_exit(CPUOFF);
	}
}

void USCI0TX_ISR(void) __attribute__((interrupt(USCIAB0TX_VECTOR)));
void USCI0TX_ISR(void) {
	//
}


