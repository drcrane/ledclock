#ifndef __RTC_H__
#define __RTC_H__

#define RTCFLAGS_UPDATETIME 1
#define RTCFLAGS_TIMESET    2

typedef struct {
	int flags;
	int prevhours;
	int hours;
	int minutes;
	int seconds;
} rtcctx_t;

extern rtcctx_t rtcctx;

void rtc_initialise();

#endif // __TIMERFN_H__
