#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// read() write()
#include <unistd.h>
#include <fcntl.h>

#include "dbg.h"
#include "minunit.h"
#include "uart.h"

#define TTY "/dev/ttyUSB0"

uart_context_t * uart_ctx;

char * writesomethingandreadit_test() {
	char * wr_buf, * rd_buf;
	int res;
	int i;

	wr_buf = malloc(1024);
	for (i = 0; i < 127; i++) {
		wr_buf[i] = (char)i;
	}
	rd_buf = malloc(1024);
	for (i = 0; i < 127; i++) {
		rd_buf[i] = 0;
	}
	uart_ctx = uart_initialise(TTY, 9600);
	res = write(uart_ctx->fd, wr_buf, 5);
	debug("write(): %d", res);
	res = read(uart_ctx->fd, rd_buf, 5);
	debug("read(): %d", res);
	// this should be 0
	debug("memcmp(): %d", memcmp(rd_buf, wr_buf, 5));
	uart_finalise(uart_ctx);
	free(wr_buf);
	free(rd_buf);
	return NULL;
}

int main(int argc, char *argv[]) {
	writesomethingandreadit_test();
}

