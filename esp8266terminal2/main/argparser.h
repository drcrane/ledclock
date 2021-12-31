#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <stddef.h>

#define ARGPARSER_MAXARGS 10

size_t argparser_check_for_eol(char * line, char * end);
int argparser_parse(char *argv[], char * input);

#endif // ARGPARSER_H

