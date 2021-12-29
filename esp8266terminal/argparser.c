#include "argparser.h"

#include <string.h>
#include <stddef.h>

size_t argparser_check_for_eol(char * line, char * end) {
	char * pos = line;
	while (pos != end) {
		int c = *pos;
		if (c == '\n' || c == '\r') {
			*pos = '\0';
			return (size_t)(pos - line);
		}
		pos ++;
	}
	return 0;
}

int argparser_parse(char * argv[], char * input) {
	int argc = 0;
	char * temp;
	char * rover;

	rover = input;
	do {
		if (*rover == '\"') {
			rover ++;
			argv[argc++] = rover;
			temp = strchr(rover, '\"');
			if (temp == NULL) {
				// not terminated!
				break;
			}
			*temp = 0;
			// skip the space after the " ;-)
			rover = temp + 2;
			continue;
		} else {
			temp = strchr(rover, ' ');
			argv[argc++] = rover;
			if (temp == NULL) {
				// got to end of string
				break;
			}
			*temp = '\0';
			rover = temp + 1;
		}
	} while (argc < ARGPARSER_MAXARGS);
	return argc;
}

