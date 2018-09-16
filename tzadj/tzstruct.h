#ifndef TIMEZONESTRUCT_H
#define TIMEZONESTRUCT_H

#include <time.h>

struct timezonechanges {
	time_t startsat;
	time_t endsat;
};

extern struct timezonechanges timezonechanges[];

int tz_shouldaddanhour(time_t epoch);

#endif // TIMEZONESTRUCT_H

