#include "tzstruct.h"
#include <time.h>
//#include <stdio.h>

int tz_shouldaddanhour(time_t epoch) {
	int i;
	i = 0;
	do {
		if (epoch > timezonechanges[i].startsat &&
				epoch < timezonechanges[i].endsat) {
			return 1;
		}
		//fprintf(stdout, "%ld: %ld %ld\n", epoch, timezonechanges[i].startsat, timezonechanges[i].endsat);
		i ++;
	} while (timezonechanges[i].startsat != 0 && epoch > timezonechanges[i].startsat);
	return 0;
}

