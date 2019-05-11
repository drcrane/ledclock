#include "tzstruct.h"
#include <time.h>
#include <stdio.h>

int tz_shouldaddanhour(time_t epoch) {
	int i;
	i = -1;
	//printf("Add Hour?\n");
	do {
		i++;
		//printf("%ld: %ld (%d) %ld (%d)\n", (long int)epoch, (long int)timezonechanges[i].startsat, (long int)epoch > (long int)timezonechanges[i].startsat, (long int)timezonechanges[i].endsat, (long int)epoch < (long int)timezonechanges[i].endsat);
		if (((long int)epoch > (long int)timezonechanges[i].startsat) &&
				((long int)epoch < (long int)timezonechanges[i].endsat)) {
			//printf("Y\n");
			return 1;
		}
		
		//printf("E: %d %d\n", (long int)timezonechanges[i].startsat != 0, (long int)epoch > (long int)timezonechanges[i].startsat);
	} while ((long int)timezonechanges[i].startsat != 0 && (long int)epoch > (long int)timezonechanges[i].startsat);
	//printf("N\n");
	return 0;
}

