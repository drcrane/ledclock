#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "dbg.h"
#include "minunit.h"

#include "argparser.h"

const char * argparser_basic_test() {
	char * line = strdup("ls -1\r\n");
	size_t line_len = strlen(line);
	line_len = argparser_check_for_eol(line, line + line_len);
	mu_assert(line_len == 5, "line_len incorrect");
	mu_assert(strlen(line) == line_len, "strlen(line) does not match line_len");
	int arg_count;
	char * args[ARGPARSER_MAXARGS];
	arg_count = argparser_parse(args, line);
	mu_assert(arg_count == 2, "incorrect argument count");
	mu_assert(strcmp(args[0], "ls") == 0, "arg 0 incorrect");
	mu_assert(strcmp(args[1], "-1") == 0, "arg 1 incorrect");
	return NULL;
}

const char * all_tests() {
	mu_suite_start();
	mu_run_test(argparser_basic_test);
	return NULL;
}

RUN_TESTS(all_tests)

