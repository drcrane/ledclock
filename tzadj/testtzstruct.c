#include <stdio.h>
#include "tzstruct.h"
#include <time.h>

int main(int argc, char *argv) {
	time_t epoch;
	int dst;

	epoch = 1711846900;
	dst = tz_shouldaddanhour(epoch);
	fprintf(stdout, "%ld Add an hour? %s\n", epoch, dst ? "Yes" : "No");

	epoch = 2045696401;
	dst = tz_shouldaddanhour(epoch);
	fprintf(stdout, "%ld Add an hour? %s\n", epoch, dst ? "Yes" : "No");

	epoch = 1887843601;
	dst = tz_shouldaddanhour(epoch);
	fprintf(stdout, "%ld Add an hour? %s\n", epoch, dst ? "Yes" : "No");

	return 0;
}

