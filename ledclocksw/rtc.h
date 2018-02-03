#ifndef __RTC_H__
#define __RTC_H__

typedef struct {
	int flags;
	int hours;
	int minutes;
	int seconds;
} rtcctx_t;

extern rtcctx_t rtcctx;

void rtc_initialise();

#endif // __TIMERFN_H__
