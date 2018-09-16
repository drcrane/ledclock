#include <stdio.h>
#include <time.h>

struct timezonechanges {
	time_t startat;
	time_t endat;
};

struct timezonechanges timezonechanges[] =
{
{ 1901149200, 1919293200 },
{ 0, 0 }
};

const int monthdays[] = {31,29,31,30,31,30,31,31,30,31,30,31};

const char * weekday_str(int dow) {
	static const char *weekdayname[] = {"Monday", "Tuesday",
		"Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	return weekdayname[dow];
}

const int weekday(int year, int month, int day) {
	size_t JND = \
		day \
		+ ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) \
		+ (365 * (year + 4800 - ((14 - month) / 12))) \
		+ ((year + 4800 - ((14 - month) / 12)) / 4)   \
		- ((year + 4800 - ((14 - month) / 12)) / 100) \
		+ ((year + 4800 - ((14 - month) / 12)) / 400) \
		- 32045;
	return (int)(JND % 7);
}

// important note, will not work for february... or might?
int getlastsundaydate(int year, int month) {
	int dom;
	int dow;
	dom = monthdays[month - 1];
	dow = weekday(year, month, dom);
	if (dow < 6) {
		dom -= (dow + 1);
	}
	return dom;
}

time_t epochfordate(int year, int month, int dom, int hour, int minute, int second) {
	struct tm t = {0};
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = dom;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = second;
	time_t timeSinceEpoch = timegm(&t);
	return timeSinceEpoch;
}

int main(void) {
	int year, month, dom;
	time_t start_epoch, end_epoch;

	printf("#include \"tzstruct.h\"\n");
	printf("\n");
	printf("struct timezonechanges timezonechanges[] = \n");
	printf("{\n");
	year = 2018;
	do {
		month = 3;
		dom = getlastsundaydate(year, month);
		// printf("%04d-%02d-%02d\n", year, month, dom);
		start_epoch = epochfordate(year, month, dom, 1, 0, 0);
		month = 10;
		dom = getlastsundaydate(year, month);
		// printf("%04d-%02d-%02d\n", year, month, dom);
		end_epoch = epochfordate(year, month, dom, 1, 0, 0);
		printf("{ %ld, %ld }, // %d\n", start_epoch, end_epoch, year);
		year ++;
	} while (year < 2035);
	printf("{ 0, 0 }\n");
	printf("};\n");
	printf("\n");

//  printf("%d-%02d-%02d: %s\n", 2011, 5, 19, wd(2011, 5, 19));
//  printf("%d-%02d-%02d: %s\n", 2038, 1, 19, wd(2038, 1, 19));
	return 0;
}

