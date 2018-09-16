#include <msp430.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "utilityfn.h"
#include "timerfn.h"
#include "rtc.h"
#include "usc.h"

const char digits[] = { 0xBF, 0x06, 0x5B, 0x4F, 0xE6, 0xED, 0xFD, 0x07, 0xFF, 0xEF, 0x99, 0xE3 };

void outputdigit(void * ptr) {
	char dst[8];
	Utility_intToHex(dst, ptr, 1);
	hwuart_sendstr(dst);
}

void printtime() {
	outputdigit(&rtcctx.hours);
	outputdigit(&rtcctx.minutes);
	outputdigit(&rtcctx.seconds);
	hwuart_sendstr("\r\n");
	//hwuart_sendstr("lwl");
}

int digit_idx;

void Timer1_A0(void) __attribute__((interrupt(TIMER1_A0_VECTOR)));
void Timer1_A0(void) {
	//P2OUT = 1;
	//P3OUT = digits[digit_idx];
}

#define TA_IFG        0x0a
#define TA_CCR1_MATCH 0x02
#define TA_CCR2_MATCH 0x04

void Timer1_A1(void) __attribute__((interrupt(TIMER1_A1_VECTOR)));
void Timer1_A1(void) {
	int digit_bitmap_idx;
	int p2val;
	// Interrupt Flag is cleared by reading TA1IV
	switch (TA1IV) {
	// Mark Period
	case TA_CCR1_MATCH:
		if (1) {
		switch (digit_idx) {
		case 0:
		{
			if (rtcctx.hours != 0) {
				digit_bitmap_idx = rtcctx.hours / 10;
			} else {
				digit_bitmap_idx = 0;
			}
			digit_idx ++;
			p2val = 0x01;
		}
		break;
		case 1:
		{
			if (rtcctx.hours != 0) {
				digit_bitmap_idx = rtcctx.hours % 10;
			} else {
				digit_bitmap_idx = 0;
			}
			digit_idx ++;
			p2val = 0x02;
		}
		break;
		case 2:
		{
			if (rtcctx.minutes != 0) {
				digit_bitmap_idx = (rtcctx.minutes / 10) % 10;
			} else {
				digit_bitmap_idx = 0;
			}
			digit_idx ++;
			p2val = 0x04;
		}
		break;
		default:
		{
			digit_bitmap_idx = rtcctx.minutes % 10;
			digit_idx = 0;
			p2val = 0x08;
		}
		//
		break;
		}
		P3OUT = digits[digit_bitmap_idx];
		P2OUT = p2val;
		//
		} else {
			// INITIALISING...
		}
		break;
	case TA_IFG:
	default:
	{
		P2OUT = 0;
	}
	break;
	}
}

uint16_t i;

int main() __attribute__ ((naked));
int main() {
	WDTCTL = WDTPW | WDTHOLD;

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	// Hold MCP23017 in RESET (P3.7)
	P3OUT &= ~(BIT7 | BIT6 | BIT5);
	P3DIR |= BIT7 | BIT6 | BIT5;

	// Initialise the UART 9600 @ 8MHz
	P1SEL |= BIT1 | BIT2;
	P1SEL2 |= BIT1 | BIT2;
	UCA0CTL1 |= UCSSEL_2 | UCSWRST;
	UCA0BR0 = 52;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRF_3 | UCOS16;
	UCA0CTL1 &= ~UCSWRST;

	IFG2 &= ~UCA0RXIFG;
	IE2 |= UCA0RXIE;

	hwuart_init();

	// Initialise the Clock / Timer
	//TA0CTL = //
	BCSCTL3 |= XCAP_3; // 12.5pF Load on XTAL
	// TASSEL_1  - SELECT ACLK
	// ID_0      - DIVIDE BY 1
	// MC_1      - COUNT UP TO TA0CCR0
	// TACLR     - CLEAR THE TA0CR REGISTER
	// TAIE      - ENABLE INTERRUPTS
	TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR; // | TAIE;
	// ONE SECOND INTERRUPTS
	TA0CCR0 = 32767;
	TA0CCTL0 = CCIE;

	UCA0TXBUF = 'I';
	while(!(IFG2 & UCA0TXIFG)) { __nop(); }

	// Turn LED ON on Demo Board
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	P3OUT = 0x0;
	P3DIR = 0xFF;

	P2OUT = 0x2 | 0x8;
	P2DIR = 0xFF;

	// ID_3 is clock /8
	// 1 cycle @ 8MHz = 0.125uS, tick once per mS: 1000.0/(0.125*8.0) = 1000
	TA1CTL = ID_3 | TASSEL_2 | MC_1 | TACLR | TAIE;
	TA1CCR0 = 2000;
	TA1CCR1 = 50;
	TA1CCTL0 = CCIE;
	TA1CCTL1 = CCIE;

	digit_idx = 0;

	rtc_initialise();
	//printtime();

	i = 65530; while (i--) { __nop(); }

	__bis_SR_register(GIE);
	__nop();

	while (1) {
		if (hwuart_flags & HWUART_HASRECEIVED) {
			// Toggle on received byte
			P1OUT ^= BIT0;
			hwuart_flags &= ~HWUART_HASRECEIVED;
			if (*hwuart_getlinebuf() == 'p') {
				printtime();
			}
			int8_t * lb = hwuart_getlinebuf();
			if (strncmp((char *)lb, "TIME", 4) == 0) {
				rtcctx.hours = Utility_aToInt((char *)lb + 4);
				rtcctx.minutes = Utility_aToInt((char *)lb + 7);
				rtcctx.seconds = Utility_aToInt((char *)lb + 10);
				//printtime();
				rtcctx.flags |= RTCFLAGS_TIMESET;
			}
			//UCA0TXBUF = hwuart_byte;
		}
		if (rtcctx.flags & RTCFLAGS_UPDATETIME) {
			hwuart_sendstr("\rtime sync beverly.bengreen.eu\r");
			rtcctx.flags &= ~RTCFLAGS_UPDATETIME;
		}
		//P3OUT = digits[rtcctx.seconds % 10];

		//timer_docallbacks();
	}
}

