#include <msp430.h>
#include <stdint.h>
#include <stddef.h>

#include "timerfn.h"

timerctx_t timeractx;

void timer_initialise() {
	int i;
	i = TIMER_MAX_CALLBACKS;
	do {
		i--;
		timeractx.callback[i] = NULL;
	} while (i != 0);
	timeractx.flags = 0;
}

/* timerctx.flags is critical. */
int timer_callback(int ticks, void (*callback)()) {
	int i;
	i = TIMER_MAX_CALLBACKS;
	do {
		i--;
		if (timeractx.callback[i] == NULL) {
			timeractx.ticks[i] = ticks;
			timeractx.callback[i] = callback;
			return 1;
		}
	} while (i != 0);
	timeractx.flags &= ~TIMER_FLAGS_EMPTY;
	return 0;
}

void timer_set_dummy() {
	timeractx.flags |= TIMER_FLAGS_DUMMY;
}

void timer_clear_dummy() {
	timeractx.flags &= ~TIMER_FLAGS_DUMMY;
}

int timer_is_present(void (*callback)()) {
	int i;
	i = TIMER_MAX_CALLBACKS;
	do {
		i--;
		if (timeractx.callback[i] == callback) {
			return 1;
		}
	} while (i != 0);
	return 0;
}

int timer_is_present_remove(void (*callback)()) {
	int i;
	i = TIMER_MAX_CALLBACKS;
	do {
		i--;
		if (timeractx.callback[i] == callback) {
			timeractx.callback[i] = NULL;
			return 1;
		}
	} while (i != 0);
	return 0;
}

void timer_wait_for(int msDelay) {
	int i;
	void (* callback)();
//	timer_callback(msDelay, timer_set_dummy);
//timer_flags_dummy:
	__bis_SR_register(LPM0_bits | GIE);
	i = TIMER_MAX_CALLBACKS;
	do {
		i--;
		if (timeractx.callback[i] != NULL && timeractx.ticks[i] == 0) {
			callback = timeractx.callback[i];
			timeractx.callback[i] = NULL;
			callback();
		}
	} while (i != 0);
//	if (timeractx.flags & TIMER_FLAGS_DUMMY) {
//		goto timer_flags_dummy;
//	}
}

void timer_docallbacks() {
	int i;
	void (* callback)();
	i = TIMER_MAX_CALLBACKS;
//	__asm__ (" mov  #6, r15\n call #logdebugpos\n" ::: "r15");
	do {
		i--;
		if (timeractx.callback[i] != NULL && timeractx.ticks[i] == 0) {
			callback = timeractx.callback[i];
			timeractx.callback[i] = NULL;
			callback();
		}
//		__asm__ (" mov  #7, r15\n call #logdebugpos\n" ::: "r15");
	} while (i != 0);
}

/*
int sendChar(int source) {
	UCA0TXBUF = 'T'; while(!(IFG2 & UCA0TXIFG)) { __nop(); }
	timer_callback(1000, sendChar);
}
*/

/*
 * Execution time to enter the ISR is 6 cycles time to exit is 5 cycles
 * At 16MHz = 0.0625uS/cycle
 * 0.6875uS for enter and exit the ISR
 */

// note that we only decrement the ticks here
// a callback will always be called in the context
// of the main thread.
/*
void Timer1_A0(void) __attribute__((interrupt(TIMER1_A0_VECTOR)));
void Timer1_A0(void) {
	int i;
	int flg;
	flg = 0;
	if (!(timeractx.flags & TIMER_FLAGS_EMPTY)) {
		i = TIMER_MAX_CALLBACKS;
		do {
			i--;
			if (timeractx.ticks[i] != 0) {
				timeractx.ticks[i] --;
			} else if (timeractx.callback[i] != NULL) {
				flg |= 1;
			}
		} while (i != 0);
	}
	if (flg) {
		__bic_SR_register_on_exit(CPUOFF);
	}
}
*/

