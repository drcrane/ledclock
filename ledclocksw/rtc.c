#include <msp430.h>
#include <stdint.h>
#include <stddef.h>

#include "rtc.h"

rtcctx_t rtcctx;

void rtc_initialise() {
	rtcctx.flags = 0;
	rtcctx.hours = 0;
	rtcctx.minutes = 0;
	rtcctx.seconds = 0;
}

void Timer0_A0(void) __attribute__((interrupt(TIMER0_A0_VECTOR)));
void Timer0_A0(void) {
	// Update Time
	rtcctx.seconds ++;
	if (rtcctx.seconds == 60) {
		rtcctx.minutes ++;
		rtcctx.seconds = 0;
		if (rtcctx.minutes == 60) {
			rtcctx.hours ++;
			rtcctx.minutes = 0;
			if (rtcctx.hours == 24) {
				rtcctx.hours = 0;
			}
		}
	}
}


